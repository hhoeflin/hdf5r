

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





##' Remove C-style comments in a character string
##'
##' The function removes all C-style comments from a string vector
##' @title Remove C-style comments in a character string
##' @param lines The lines of the C code
##' @param remove_empty_lines Should empty code lines be removed as well
##' @return Returns the lines, but with the c-comments removed  
##' @author Holger Hoefling
##' @export
remove_c_comments <- function(lines, remove_empty_lines=TRUE) {
    in_slash_star_comment <- FALSE
    for(line_num in seq_along(lines)) {
        ## process one line at a time
        line_finished <- FALSE
        char_pos <- 1
        while(char_pos <= nchar(lines[line_num])) {
            if(in_slash_star_comment) {
                ## see if we can find the end
                hits <- gregexpr("*/", lines[line_num], fixed=TRUE)[[1]]
                hits <- hits[hits >=char_pos]
                if(length(hits) > 0) {
                    ## found end of comment in current line
                    ## remove the comment
                    lines[line_num] <- paste0(substr(lines[line_num], start=1, stop=char_pos-1),
                                              substr(lines[line_num], start=hits[1]+2, stop=nchar(lines[line_num])))
                    char_pos <- hits[1] + 2
                    in_slash_star_comment <- FALSE
                }
                else {
                    ## if an entire line is removed ... set to NA so that we can later delete it
                    ## line from char_pos to end is a comment 
                    lines[line_num] <- substr(lines[line_num], start=1, stop=char_pos - 1)
                    char_pos <- nchar(lines[line_num]) + 1
                }
            }
            else {
                ## search for the beginning of any style comment
                hits_dblslash <- gregexpr("//", lines[line_num], fixed=TRUE)[[1]]
                hits_dblslash <- hits_dblslash[hits_dblslash >= char_pos]
                hits_slash_star <- gregexpr("/*", lines[line_num], fixed=TRUE)[[1]]
                hits_slash_star <- hits_slash_star[hits_slash_star >= char_pos]

                if(length(hits_dblslash) > 0 && length(hits_slash_star) > 0) {
                    if(hits_dblslash[1] < hits_slash_star[1]) {
                        ## delete everything to the end of the line
                        lines[line_num] <- substr(lines[line_num], start=1, stop=hits_dblslash[1] -1)
                    }
                    else {
                        char_pos <- hits_slash_star[1]
                        in_slash_star_comment <- TRUE
                    }
                }
                else if(length(hits_dblslash) > 0) {
                        ## delete everything to the end of the line
                        lines[line_num] <- substr(lines[line_num], start=1, stop=hits_dblslash[1] -1)
                }
                else if(length(hits_slash_star) > 0) {
                        char_pos <- hits_slash_star[1]
                        in_slash_star_comment <- TRUE
                }
                else {
                    ## nothing to do on this line
                    char_pos <- nchar(lines[line_num]) + 1
                }
            }
        }
    }
    if(remove_empty_lines) {
        empty_lines <- grepl("^\\s*$", lines, perl=TRUE)
        lines[empty_lines]  <- ""
    }
    return(lines)
}

##' Remove comments from a file and write it out again
##'
##' Reads in a file, removes the C-style comments and writes it back out
##' @title Remove comments from a file and write it out again
##' @param infile The original file to remove the comments from
##' @param outfile The file were the content without comments is written
##' @return invisible \code{NULL}
##' @author Holger Hoefling
##' @export
remove_c_comments_from_file <- function(infile, outfile) {
    lines <- readLines(infile)
    lines <- remove_c_comments(lines)
    cat(lines, file=outfile, sep="\n")
    return(invisible(NULL))
}
