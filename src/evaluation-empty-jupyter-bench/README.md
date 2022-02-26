# Jupyter Lab

This is just an empty project that installs the Jupyter Lab environment.

## Running the environment

This requires [Python Poetry](https://python-poetry.org) and also installs the R kernel.

```shell
poetry install
poetry run Rscript -e 'install.packages ("IRkernel") ; IRkernel::installspec ()'
poetry run jupyter lab
```
