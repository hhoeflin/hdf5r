.ONESHELL:
R=R


.PHONY: all clean copy


all: ./create_constants_wrapper.Rout ./createCWrappers.Rout ./create_datatype_wrappers.Rout ./identify_prototypes.Rout




output/all_const_df_code.txt output/all_const_enum_names.txt ./create_constants_wrapper.Rout: create_constants_wrapper.R all_const.csv
	$(R) CMD BATCH --no-save --no-restore --no-site-file --no-environ create_constants_wrapper.R ./create_constants_wrapper.Rout

output_code/export_auto.h output/library_names.txt output/makevars_files.txt ./createCWrappers.Rout output/include_file_names.txt: createCWrappers.R helperFunctions.R injectionCode.R store/functions_for_wrappping.rds
	$(R) CMD BATCH --no-save --no-restore --no-site-file --no-environ createCWrappers.R ./createCWrappers.Rout
	cd output_code && patch -F 0 < ../patches/empty_attrs.patch

output/DT_enum_base_type.txt output/DT_enum_enum.txt output/enum_assign.txt output/base_type_assign.txt output/DT_enum_struct.txt output/enum_create_code_c.txt output/enum_create_code_h.txt output/struct_create_code_h.txt output/DT_enum_all_types.txt output/h5t_public_types_assign.txt output/all_types_dt_return_df.txt output/struct_create_code_c.txt ./create_datatype_wrappers.Rout output/struct_assign.txt: store/all_types.rds create_datatype_wrappers.R store/enum_info.rds store/struct_info.rds
	$(R) CMD BATCH --no-save --no-restore --no-site-file --no-environ create_datatype_wrappers.R ./create_datatype_wrappers.Rout

store/functions_for_wrappping.rds store/all_types.rds store/struct_info.rds store/enum_info.rds ./identify_prototypes.Rout output/HelperTypedefs.h: FindAndReplace.R identify_prototypes.R helperFunctions.R
	$(R) CMD BATCH --no-save --no-restore --no-site-file --no-environ identify_prototypes.R ./identify_prototypes.Rout


clean:
	rm -r output_code output store src_nocomments *.Rout

copy:
	mkdir -p ../../src/1_10_2
	cp output_code/*.h output_code/*.c ../../src/1_10_2
