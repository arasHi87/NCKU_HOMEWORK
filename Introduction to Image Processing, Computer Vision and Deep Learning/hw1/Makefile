PKG=src

.PHONY: clean init

init: clean
	poetry install
	poetry run pre-commit install

run:
	poetry run python3 ${PKG}/main.py

lint:
	poetry run flake8 ${PKG}/ --max-line-length=120
	poetry run pylint --rcfile=setup.cfg ${PKG}/*

format:
	poetry run black ${PKG}/
	poetry run isort .