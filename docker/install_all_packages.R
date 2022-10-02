install.packages(c("devtools", "testthat", "bit64", "knitr", "rmarkdown", "formatR", "nycflights13", "reshape2", "R6"), repos='http://cran.us.r-project.org')
library(devtools)
options(unzip = 'internal')
install_github("hhoeflin/roxygen", force=TRUE)
install_github("hadley/pkgdown")



