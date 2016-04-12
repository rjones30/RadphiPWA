all: PWAtool_cc.so omega_C.so

PWAtool_cc.so: PWAtool.cc PWAtool.h PWAtool_dict.C
	g++ -fPIC -g -shared -o $@ -I. -I$(ROOTSYS)/include $< PWAtool_dict.C `root-config --libs`
	#root -q -b makerootlibs.C

omega_C.so: omega.C omega.h omega_dict.C
	g++ -fPIC -g -shared -o $@ -I. -I$(ROOTSYS)/include $< omega_dict.C `root-config --libs`

omega_dict.C: omega.h
	@rm -f omega_dict.*
	rootcint $@ -c $^

PWAtool_dict.C: PWAtool.h
	@rm -f PWAtool_dict.*
	rootcint $@ -c $^
