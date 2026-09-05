# On Release

On release, run tests on the following sites:

## Check reverse dependencies

Any reverse dependencies should be checked before merging.

## For linux

Run it in my local docker.

Also use R-hub's Linux runner locally.

Build the harness R-devel installation, configure an R-hub token once with
`rhub::rc_new_token()`, and install the submission dependencies with:

    gmake -C harness build-macos-r R_VERSION=devel
    gmake submit-deps

Then submit the Linux check with:

    make submit-rhub

Submission targets use harness R-devel and the dedicated
`harness/installs/R-libs-submission/devel` library.

Set `RHUB_PLATFORMS` to a comma-separated list to select other R-hub runners.


## For Mac

[Mac builder](https://mac.r-project.org/macbuilder/submit.html)

Submit the built package with:

    make submit-macbuilder

Set `MAC_DEPFILES` to a comma-separated list of custom dependency files when
needed.


## For windows

[Win builder](https://win-builder.r-project.org/)

Submit to all available Win-builder versions with:

    make submit-winbuilder

Set `WINBUILDER_VERSIONS` to a comma-separated subset of `R-release`,
`R-devel`, and `R-oldrelease` when needed.

To submit to all three services in sequence, run:

    make submit-checkers
