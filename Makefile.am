SUBDIRS = data src

EXTRA_DIST=ChangeLog glpong.spec

.PHONY : rpm deb packages doc
rpm: dist
	cp $(PACKAGE)-$(VERSION).tar.gz /usr/src/redhat/SOURCES/
	rpm -ba $(PACKAGE).spec
	cp /usr/src/redhat/RPMS/i386/$(PACKAGE)-$(VERSION)-*.i386.rpm .
	cp /usr/src/redhat/SRPMS/$(PACKAGE)-$(VERSION)-*.src.rpm .

deb:
	debian/rules
	debuild
	debc
	debi
	release

packages: rpm deb

doc:
	cd doc && make doc

