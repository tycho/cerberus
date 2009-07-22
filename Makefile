all:
	cd contrib/crisscross; cmake .; cd ../..
	$(MAKE) -C contrib/crisscross CrissCross
#	$(MAKE) -C contrib/crisscross check
	$(MAKE) -f source/Makefile

clean:
	$(MAKE) -f source/Makefile clean

distclean: clean
	$(MAKE) -C contrib/crisscross clean

contrib:
	$(MAKE) -C contrib/crisscross
