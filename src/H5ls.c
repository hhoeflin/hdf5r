
/**************************************************************************
 * 
 * Copyright 2016 Novartis Institutes for BioMedical Research Inc.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *************************************************************************/


#include "H5ls.h"



typedef struct H5L_op_data {
  hsize_t num_visited;
  hsize_t num_allocated;
  hid_t lapl_id;
  hid_t dapl_id;
  hid_t tapl_id;
  H5ls_info_t* ls_info;
} H5L_op_data;


#define max_char_int64 30


herr_t H5Dget_info(hid_t d_id, H5D_info_t * dataset_info) {
  // first get the space and its class

  hid_t s_id = H5Dget_space(d_id);
  if(s_id < 0) {
    return(s_id); // return the negtive number as the error message
  }

  hid_t t_id = H5Dget_type(d_id);
  if(t_id < 0) {
    H5Sclose(s_id);
    return(t_id);
  }

  // get the dataset and space type
  dataset_info->type_class = H5Tget_class(t_id);
  dataset_info->space_class = H5Sget_simple_extent_type(s_id);

  // get the dimensions of the dataspace if it is simple
  if(dataset_info->space_class == H5S_SIMPLE) {
    int rank = H5Sget_simple_extent_ndims(s_id);
    dataset_info->rank = rank;
    if(rank > 0) {
      // allocate 30 characters per dimension, to be safe
      const int alloc_size = rank * max_char_int64;
      dataset_info->dims = R_alloc(1, alloc_size);
      dataset_info->maxdims = R_alloc(1, alloc_size);
      
      // now get the dimensions
      hsize_t dims[rank];
      hsize_t maxdims[rank];

      int num_dim = H5Sget_simple_extent_dims(s_id, dims, maxdims);
      if(num_dim < 0) {
	// some sort of error occured
	dataset_info->dims = "-";
	dataset_info->maxdims = "-";
      }
      else {
	int dims_char_written = 0;
	int maxdims_char_written = 0;
	for(int i = rank - 1; i >= 0; --i) {
	  dims_char_written += snprintf(dataset_info->dims + dims_char_written, alloc_size, "%llu", dims[i]);
	  if(i > 0) {
	    dims_char_written += snprintf(dataset_info->dims + dims_char_written, alloc_size, " x ");
	  }

	  // now the maxdims; need to check for inf
	  if (maxdims[i] == H5S_UNLIMITED) {
	    maxdims_char_written += snprintf(dataset_info->maxdims + maxdims_char_written, alloc_size, "Inf");
	  }
	  else {
	    maxdims_char_written += snprintf(dataset_info->maxdims + maxdims_char_written, alloc_size, "%llu", maxdims[i]);
	  }
	  if(i > 0) {
	    maxdims_char_written += snprintf(dataset_info->maxdims + maxdims_char_written, alloc_size, " x ");
	  }
	}
      }
    }
  }
  else if(dataset_info->space_class == H5S_SCALAR) {
    dataset_info->rank = 0;
    dataset_info->dims = "0";
    dataset_info->maxdims = "0";
  }
  else {
    dataset_info-> rank = -1;
    dataset_info->dims = "-";
    dataset_info->maxdims = "-";
  }
 
  H5Tclose(t_id);
  H5Sclose(s_id);
  return(0);
}

herr_t H5Dget_info_by_name(hid_t g_id, const char* name, H5D_info_t * dataset_info, hid_t dapl_id) {
  // Open the dataset; we will use the 1.10 API
  hid_t d_id = H5Dopen2(g_id, name, dapl_id);
  if(d_id < 0) {
    return(d_id);
  }
  
  herr_t err;
  // get the dataset info
  err = H5Dget_info(d_id, dataset_info);
  H5Dclose(d_id);
  return(err);
}


herr_t gather_data_from_link(hid_t g_id, const char *name, const H5L_info_t *info, void *op_data) {
  H5L_op_data* lsdata_ptr = op_data;
  H5ls_info_t* ls_info=lsdata_ptr->ls_info + lsdata_ptr->num_visited; // this is the current one we are editing

  // first check if we have allocated space; if not - just increase the counter
  if(lsdata_ptr->num_visited < lsdata_ptr->num_allocated) {
    //Rprintf("Storing info on a link %s\n", name);
    // save the name of the link
    ls_info->name=R_alloc(1, strlen(name) + 1);
    strcpy(ls_info->name, name);
    // collect the data
    // this part of the functionality expects that automatic error collection is turned off
    ls_info->link_success=1;
    ls_info->link = *info;

    // now also grab the object info
    //Rprintf("Started getting object info\n");
    // first need to open the object, then get its type, then close it again
    hid_t obj_id;
    herr_t err;
    obj_id = H5Oopen(g_id, name, lsdata_ptr->lapl_id);
    //Rprintf("Finished getting object info\n");
    if(obj_id >= 0) {
      // everything ok
      H5I_type_t obj_type;
      int num_attrs;
      obj_type = H5Iget_type(obj_id);
      num_attrs = H5Aget_num_attrs(obj_id);
      err = H5Oclose(obj_id);
      ls_info->obj_type_success=1;
      ls_info->obj_type=obj_type;
      ls_info->num_attrs = num_attrs;
    }
    else {  // this is intended to let us count how many items we have in the end
      ls_info->obj_type_success=0; // not really necessary; already initialized to 0
      // if getting the object failed, we are done
      lsdata_ptr->num_visited++;
      return(0);
    }

    // We know that we could access the object; grab data specific to the object type
    if(ls_info->obj_type == H5I_GROUP) {
      // grab group info if it is a group
      H5G_info_t group_info;
      err = H5Gget_info_by_name(g_id, name, &group_info, lsdata_ptr->lapl_id);
      if(err >= 0) {
	ls_info->group_success=1;
	ls_info->group = group_info;
      }
      else {
	ls_info->group_success=0;
      }
    }
    else if(ls_info->obj_type == H5I_DATASET) {
      // grab dataset info if it is a dataset
      H5D_info_t dataset_info;
      //Rprintf("Getting dataset info\n");
      err = H5Dget_info_by_name(g_id, name, &dataset_info, lsdata_ptr->dapl_id);
      //Rprintf("Finished dataset info\n");
      if(err >= 0) {
	ls_info->dataset_success=1;
	ls_info->dataset = dataset_info;
      }
      else {
	ls_info->dataset_success=0;
      }
    }
    else if(ls_info->obj_type == H5I_DATATYPE) {
      // grab datatype class if it is a datatype
      hid_t named_dt = H5Topen2(g_id, name, lsdata_ptr->tapl_id);
      if(named_dt >= 0) {
	ls_info->committed_type = H5Tget_class(named_dt);
	ls_info->type_success = 1;
      }
      else {
	ls_info->type_success = 0;
	ls_info->committed_type=H5T_NO_CLASS;
      }
      H5Tclose(named_dt);
    }
  }
  lsdata_ptr->num_visited++;
  //Rprintf("Counting link %s\n", name);
  return(0);
}



// gather the information on the contents of a group
// if recurse, the will use H5Lvisit, otherwise H5Literate
// all this complexity does not need to be exposed here, 
// so will keep the interface as simple as possible 
SEXP R_H5ls(SEXP _g_id, SEXP _recursive, SEXP _index_type, SEXP _order, SEXP _lapl_id, SEXP _dapl_id, SEXP _tapl_id) {

  hid_t g_id = SEXP_to_longlong(_g_id, 0);
  int recursive = SEXP_to_logical(_recursive); 
  herr_t err;
  H5_index_t index_type = SEXP_to_longlong(_index_type, 0);
  H5_iter_order_t order = SEXP_to_longlong(_order, 0);

  SEXP robj_ls_info = R_NilValue; // will use it to allocate space for the ls_info struct

  // need to prepare lsdata for the first pass
  // first pass will be with no allocated space to see how much we need
  H5L_op_data lsdata;
  lsdata.lapl_id = SEXP_to_longlong(_lapl_id, 0);
  lsdata.dapl_id = SEXP_to_longlong(_dapl_id, 0);
  lsdata.tapl_id = SEXP_to_longlong(_tapl_id, 0);
  lsdata.num_visited = 0;
  lsdata.num_allocated = 0;

  if(recursive) {
    // run it with H5Lvisit
    err = H5Lvisit(g_id, index_type, order, &gather_data_from_link, &lsdata);
    if(err < 0) {
      error("Could not iterate through group for ls");
    }
  }
  else {
    // run it with H5Literate
    hsize_t iter_pos = 0;
    err = H5Literate(g_id, index_type, order, &iter_pos, &gather_data_from_link, &lsdata);
    if(err < 0) {
      error("Could not iterate through group for ls");
    }
  }

  // now allocate the necesary space
  robj_ls_info = PROTECT(H5ToR_Pre(h5_datatype[DT_H5ls_info_t], lsdata.num_visited));
  // set it to 0, just to be sure; for H5ToR_Pre usually not necessary, but here we do it anyway
  R_xlen_t vec_size = XLENGTH(robj_ls_info);
  memset(VOIDPTR(robj_ls_info), 0, vec_size);

  lsdata.ls_info = (H5ls_info_t*) VOIDPTR(robj_ls_info);
 

  // Rprintf("Number of objects visisted %d\n", lsdata.num_visited);
  lsdata.num_allocated = lsdata.num_visited;
  lsdata.num_visited = 0;
  // and the same as before
  if(recursive) {
    // run it with H5Lvisit
    err = H5Lvisit(g_id, index_type, order, &gather_data_from_link, &lsdata);
    if(err < 0) {
      error("Could not iterate through group for ls");
    }
  }
  else {
    // run it with H5Literate
    hsize_t iter_pos = 0;
    err = H5Literate(g_id, index_type, order, &iter_pos, &gather_data_from_link, &lsdata);
    if(err < 0) {
      error("Could not iterate through group for ls");
    }
  }
  // need to wrap up the results
  // will only return the dataframe
  // Rprintf("Before _Post\n");
  SEXP _return_val = PROTECT(H5ToR_Post(robj_ls_info, h5_datatype[DT_H5ls_info_t], lsdata.num_visited, H5TOR_CONV_INT64_NOLOSS, -1));
  // Rprintf("After _Post\n");

  // put it into a return list
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 1));
  SET_VECTOR_ELT(__ret_list, 0, _return_val);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 1));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_NAMES(__ret_list, __ret_list_names);

  UNPROTECT(4);
  return(__ret_list);
}

herr_t attr_info(hid_t loc_id, const char *name, const H5A_info_t *ainfo, void *opdata) {
  if( strcmp(name, "NA") == 0) {
    SET_STRING_ELT(opdata, ainfo->corder, NA_STRING);
  } else {
    SET_STRING_ELT(opdata, ainfo->corder, mkChar(name));
  }
  return 0;
}

