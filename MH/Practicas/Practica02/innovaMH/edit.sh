#!/bin/env sh
#!/bin/env sh
export JULIA_PROJECT=.

if [ ! -e Manifest.toml ]; then
    julia -e 'using Pkg; Pkg.instantiate()'
fi
julia -e 'using Pluto; Pluto.run()'
