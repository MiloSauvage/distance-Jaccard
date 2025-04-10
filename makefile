.PHONY: clean dist

dist: clean
	tar -hzcf "facqukyl.tar.gz" bst/* scale/* str/* dist-jacc-test/* stream/* makefile

clea,:
	$(MAKE) -C dist-jacc-test clean
