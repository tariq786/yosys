
OBJS += passes/techmap/techmap.o
OBJS += passes/techmap/simplemap.o
OBJS += passes/techmap/dfflibmap.o
OBJS += passes/techmap/maccmap.o
OBJS += passes/techmap/libparse.o

ifneq ($(SMALL),1)
OBJS += passes/techmap/iopadmap.o
OBJS += passes/techmap/hilomap.o
OBJS += passes/techmap/extract.o
OBJS += passes/techmap/alumacc.o
OBJS += passes/techmap/dff2dffe.o
OBJS += passes/techmap/dffinit.o
OBJS += passes/techmap/pmuxtree.o
OBJS += passes/techmap/muxcover.o
endif

GENFILES += passes/techmap/techmap.inc

passes/techmap/techmap.inc: techlibs/common/techmap.v
	$(P) echo "// autogenerated from $<" > $@.new
	$(Q) echo "static char stdcells_code[] = {" >> $@.new
	$(Q) od -v -td1 -An $< | $(SED) -e 's/[0-9][0-9]*/&,/g' >> $@.new
	$(Q) echo "0};" >> $@.new
	$(Q) mv $@.new $@

passes/techmap/techmap.o: passes/techmap/techmap.inc

ifneq ($(CONFIG),emcc)
TARGETS += yosys-filterlib$(EXE)
EXTRA_OBJS += passes/techmap/filterlib.o

yosys-filterlib$(EXE): passes/techmap/filterlib.o
	$(P) $(CXX) -o yosys-filterlib$(EXE) $(LDFLAGS) $^ $(LDLIBS)
endif

