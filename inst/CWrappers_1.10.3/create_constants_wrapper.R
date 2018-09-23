
#############################################################################
##
## Copyright 2016 Novartis Institutes for BioMedical Research Inc.
## Licensed under the Apache License, Version 2.0 (the "License");
## you may not use this file except in compliance with the License.
## You may obtain a copy of the License at
##
## http://www.apache.org/licenses/LICENSE-2.0
##
## Unless required by applicable law or agreed to in writing, software
## distributed under the License is distributed on an "AS IS" BASIS,
## WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
## See the License for the specific language governing permissions and
## limitations under the License.
##
#############################################################################





library(brew)
dir.create("output", showWarnings=FALSE)
dir.create("output_code", showWarnings=FALSE)
all_const <- read.csv("all_const.csv", stringsAsFactors=FALSE)
all_const$name <- gsub("\\s*", "", all_const$name)
all_const$name_enum <- paste0("CONST_", all_const$name)


code_df_all_const <- function(all_const) {
    code <- "SEXP show_all_const_data_frame(void) {"
    ## create the basis of the data frame
    code <- c(code, "  SEXP df = PROTECT(allocVector(VECSXP, 3));")
    code <- c(code, "  SET_VECTOR_ELT(df, 0, NEW_CHARACTER(CONST_LAST_ITEM));")
    code <- c(code, "  SET_VECTOR_ELT(df, 1, NEW_CHARACTER(CONST_LAST_ITEM));")
    code <- c(code, "  SEXP R_const = PROTECT(NEW_NUMERIC(CONST_LAST_ITEM));")
    code <- c(code, "  SET_CLASS(R_const, ScalarString(mkChar(\"integer64\")));")
    code <- c(code, "  SET_VECTOR_ELT(df, 2, R_const);")
    code <- c(code, "  SEXP df_rownames = PROTECT(NEW_INTEGER(CONST_LAST_ITEM));")
    code <- c(code, "  for(R_xlen_t i = 0; i < CONST_LAST_ITEM; ++i) {")
    code <- c(code, "    INTEGER(df_rownames)[i] = i + 1;")
    code <- c(code, "  }")
    code <- c(code, "  SET_CLASS(df, mkString(\"data.frame\"));")
    code <- c(code, "  SET_ATTR(df, install(\"row.names\"), df_rownames);")
    code <- c(code, "  SEXP df_names = PROTECT(NEW_CHARACTER(3));")
    code <- c(code, "  SET_STRING_ELT(df_names, 0, mkChar(\"Category\"));")
    code <- c(code, "  SET_STRING_ELT(df_names, 1, mkChar(\"Name\"));")
    code <- c(code, "  SET_STRING_ELT(df_names, 2, mkChar(\"Constant\"));")
    code <- c(code, "  SET_NAMES(df, df_names);")
    ## get pointers to the 4 items for easier use
    code <- c(code, "  SEXP R_categ = VECTOR_ELT(df, 0);")
    code <- c(code, "  SEXP R_name = VECTOR_ELT(df, 1);")
    code <- c(code, "  R_const = VECTOR_ELT(df, 2);")
    ## and now set the actual ids
    for(i in seq_len(nrow(all_const))) {
        code <- c(code, "")
        code <- c(code, paste0("  SET_STRING_ELT(R_categ, ", all_const$name_enum[i], ", mkChar(\"", all_const$category[i], "\"));"))
        code <- c(code, paste0("  SET_STRING_ELT(R_name, ", all_const$name_enum[i], ", mkChar(\"", all_const$name[i], "\"));"))
        code <- c(code, paste0("  ((long long *) REAL(R_const))[", all_const$name_enum[i], "] = (long long) ", all_const$name[i], ";"))
    }

    code <- c(code, "  UNPROTECT(4);")
    code <- c(code, "  return(df);")
    code <- c(code, "}")
}


cat(code_df_all_const(all_const), sep="\n", file=file.path("output", "all_const_df_code.txt"))
cat(all_const$name_enum, sep=",\n", file=file.path("output", "all_const_enum_names.txt"))

const_export_h_env <- new.env()
const_export_h_env$const_names <- paste(paste0("  ", all_const$name_enum), collapse = ",\n")
brew(file="const_export_h.brew", file.path("output_code", "const_export.h"), envir = const_export_h_env)

const_export_c_env <- new.env()
const_export_c_env$all_const_code <- paste(code_df_all_const(all_const), collapse = "\n")
brew(file="const_export_c.brew", file.path("output_code", "const_export.c"), envir = const_export_c_env)

