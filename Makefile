all: PWAtool_cc.so

PWAtool_cc.so: PWAtool.cc PWAtool.h
	root -q -b makerootlibs.C
