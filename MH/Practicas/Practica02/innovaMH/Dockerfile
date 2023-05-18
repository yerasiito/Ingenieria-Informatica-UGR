FROM docker.io/library/julia:1.8.5-bullseye
WORKDIR /app
COPY . /app
RUN rm -f /app/Manifest.toml
RUN julia --project=/app -e 'using Pkg; Pkg.instantiate(); Pkg.build()'
EXPOSE 1234
CMD julia --project=/app -e 'using Pluto; Pluto.run(; host="0.0.0.0", port=1234, launch_browser=false, disable_writing_notebook_files=true)'
