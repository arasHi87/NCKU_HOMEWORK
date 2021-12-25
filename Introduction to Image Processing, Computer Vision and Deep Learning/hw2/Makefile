PKG=src

.PHONY: clean init

init: clean
	poetry install

lint:
	poetry run flake8 ${PKG}/ --max-line-length=120
	poetry run pylint --rcfile=setup.cfg ${PKG}/*

format:
	poetry run black ${PKG}/
	poetry run isort .