#!/bin/env sh
export JULIA_PROJECT=.

if [ ! -e Manifest.toml ]; then
   julia --project=. -e 'using Pkg; Pkg.instantiate()'
fi
julia --project=. -e 'using Pluto; Pluto.run(disable_writing_notebook_files=true)'
