CC=g++
CFLAGS = -I.
LIBS = /home/admin/Dev/C/myHAS/build/myHAS_Lib
DEPS = myHAS_Daemon.h
ODIR=../build/obj
BDIR=../build

_OBJ = myHAS_MQTTd.o myHAS_Daemon.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

All: $(BDIR)/myHAS_MQTTd

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BDIR)/myHAS_MQTTd: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
