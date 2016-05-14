# william k. johnson 2015
#
# compiler flags
#
# a tsunami of macros or regular expression globbing?
# globbing is hard to read - we go with the tsunami
#
CC     = clang
CFLAGS = -fPIC -Wall -rdynamic -Qunused-arguments  -I../include \
		 								 -I/usr/include/glib-2.0 \
										 -I/usr/lib/i386-linux-gnu/glib-2.0/include \
										 -I$(DEV)/include \
										 -I$(DEV)/include/fuse3 \
										 -I./cci/service
										 -D_FILE_OFFSET_BITS=64 
LDFLAGS = -L$(DEV)/lib -shared -fPIC -lglib-2.0 -L./debug/lib -L./release/lib
LDSERVICEFLAGS = -lrdkafka -lfuse3 -lcassandra -lrabbitmq -lzookeeper_mt -lunwind  \
				-levent -lthrift -lthriftnb
LDSERVICEFLAGS += $(LDFLAGS)
LDBINFLAGS = -lpthread -lcci_cutils  -lcci_cinterface -lglib-2.0 -lrdkafka -lfuse3 -lzookeeper_mt \
			 -lcassandra -lrabbitmq -lunwind -L/dev_tools/lib -L./debug/lib -L./release/lib  
TARGET_LIB = libcci_cutils.so 
TARGET_INTERFACE_LIB = libcci_cinterface.so
TARGET_CYBER_LIB = libcci_cyber_utils.so
TARGET_SERVICE_LIB = libcci_service.so
TARGET_BIN = chromatic-c-test
TARGET_MINI_KAFKA_BIN = mini_kafka_run
#
# project files
#
SRC_DIR = ./
LIB_DIR = $(DEV_LIB)#/dev_tools/lib
CCI_DIR = $(SRC_DIR)cci
SRCS = $(CCI_DIR)/cci_utils.c
INTERFACE_SRCS = $(CCI_DIR)/cci_mini_stack.c $(CCI_DIR)/cci_mini_except.c \
				 $(CCI_DIR)/cci_mini_assert.c $(CCI_DIR)/cci_memory_utils.c \
				 $(CCI_DIR)/cci_mini_list.c $(CCI_DIR)/cci_mini_trace.c
CYBER_SRCS =  $(CCI_DIR)/cyber/cci_access_ctl.c
SERVICE_SRCS = $(CCI_DIR)/service/cci_mini_kafka.c $(CCI_DIR)/service/cci_mini_cassandra.c \
			   $(CCI_DIR)/fuser/cci_mini_fuser.c $(CCI_DIR)/service/cci_mini_rabbit.c \
			   $(CCI_DIR)/service/cci_mini_zookeeper.c
BIN_SRCS = $(SRC_DIR)test/chromatic_c_test.c
MINI_RUN_SRCS = $(CCI_DIR)/mini-run/mini_kafka_run.c \
				$(CCI_DIR)/service/cci_mini_kafka.c 
OBJS = cci_utils.o
BIN_OBJS = chromatic_c_test.o
INTERFACE_OBJS = cci_mini_stack.o cci_mini_except.o \
				 cci_mini_assert.o cci_memory_utils.o \
				 cci_mini_list.o cci_mini_trace.o
CYBER_OBJS = cci_access_ctl.o
SERVICE_OBJS = cci_mini_kafka.o cci_mini_cassandra.o \
			   cci_mini_fuser.o cci_mini_rabbit.o cci_mini_zookeeper.o
MINI_RUN_OBJS = mini_kafka_run.o  cci_mini_kafka.o 
#
# debug build settings
#
DBGDIR = debug
DBGLIB = $(DBGDIR)/$(TARGET_LIB)
DBGINTERFACELIB = $(DBGDIR)/$(TARGET_INTERFACE_LIB)
DBGCYBERLIB = $(DBGDIR)/$(TARGET_CYBER_LIB)
DBGSERVICELIB = $(DBGDIR)/$(TARGET_SERVICE_LIB)
DBGBIN = $(DBGDIR)/$(TARGET_BIN)
DBGOBJS = $(addprefix $(DBGDIR)/, $(OBJS))
DBGBINOBJS = $(addprefix $(DBGDIR)/, $(BIN_OBJS))
DBGINTERFACEOBJS = $(addprefix $(DBGDIR)/, $(INTERFACE_OBJS))
DBGCYBEROBJS = $(addprefix $(DBGDIR)/, $(CYBER_OBJS))
DBGSERVICEOBJS = $(addprefix $(DBGDIR)/, $(SERVICE_OBJS))
DBGMINIRUNBINOBJS = $(addprefix $(DBGDIR)/, $(MINI_RUN_OBJS))
DBGMINIRUNKAFKA = $(DBGDIR)/$(TARGET_MINI_KAFKA_BIN)
DBGCFLAGS = -g -O0 -DDEBUG -pg 

#
# release build settings
#
RELDIR = release
RELLIB = $(RELDIR)/$(TARGET_LIB)
RELINTERFACELIB = $(RELDIR)/$(TARGET_INTERFACE_LIB)
RELCYBERLIB = $(RELDIR)/$(TARGET_CYBER_LIB)
RELSERVICELIB = $(RELDIR)/$(TARGET_SERVICE_LIB)
RELBIN = $(RELDIR)/$(TARGET_BIN)
RELOBJS = $(addprefix $(RELDIR)/, $(OBJS))
RELBINOBJS = $(addprefix $(RELDIR)/, $(BIN_OBJS))
RELINTERFACEOBJS = $(addprefix $(RELDIR)/, $(INTERFACE_OBJS))
RELCYBEROBJS =  $(addprefix $(RELDIR)/, $(CYBER_OBJS))
RELSERVICEOBJS = $(addprefix $(RELDIR)/, $(SERVICE_OBJS))
RELMINIRUNBINOBJS = $(addprefix $(RELDIR)/, $(MINI_RUN_OBJS))
RELMINIRUNKAFKA = $(RELDIR)/$(TARGET_MINI_KAFKA_BIN)
RELCFLAGS = -O3 -DNDEBUG

.PHONY: all clean debug-core prep release-core \
		remake tree service core

# default build
all: prep release-core debug-core service tree

core: prep debug-core release-core tree

#)
# debug rules
#)
debug-core: $(DBGLIB) $(DBGINTERFACELIB) $(DBGCYBERLIB) $(DBGBIN) 

$(DBGLIB): $(DBGOBJS)
	echo $(DBGLIB)
	$(CC) $(CFLAGS) $(DBGCFLAGS) $(LDFLAGS) -o $(DBGLIB) $^
	
$(DBGINTERFACELIB): $(DBGINTERFACEOBJS)
	$(CC) $(CFLAGS) $(DBGCFLAGS) $(LDFLAGS) -o $(DBGINTERFACELIB) $^

$(DBGCYBERLIB): $(DBGCYBEROBJS)
	$(CC) $(CFLAGS) $(DBGCFLAGS) $(LDFLAGS) -o $(DBGCYBERLIB) $^
	mv $(DBGLIB) $(DBGDIR)/lib 
	mv $(DBGCYBERLIB) $(DBGDIR)/lib 
	mv $(DBGINTERFACELIB) $(DBGDIR)/lib 
	
$(DBGBIN): $(DBGBINOBJS)
	$(CC) $(CFLAGS) $(DBGCFLAGS) $(LDBINFLAGS) -o $(DBGBIN) $^
	mv $(DBGBIN) $(DBGDIR)/bin

$(DBGDIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $(DBGCFLAGS) -o $@ $<

$(DBGDIR)/%.o: $(CCI_DIR)/%.c
	$(CC) -c $(CFLAGS) $(DBGCFLAGS) -o $@ $<

$(DBGDIR)/%.o: $(CCI_DIR)/cyber/%.c
	$(CC) -c $(CFLAGS) $(DBGCFLAGS) -o $@ $<

$(DBGDIR)/%.o: $(SRC_DIR)test/%.c
	$(CC) -c $(CFLAGS) $(DBGCFLAGS) -o $@ $<

#
# release rules
#
release-core: $(RELLIB) $(RELINTERFACELIB) $(RELCYBERLIB) $(RELBIN) 

$(RELLIB): $(RELOBJS) $
	$(CC) $(CFLAGS) $(RELCFLAGS) $(LDFLAGS) -o $(RELLIB) $^

$(RELINTERFACELIB): $(RELINTERFACEOBJS)
	$(CC) $(CFLAGS) $(RELCFLAGS) $(LDFLAGS) -o $(RELINTERFACELIB) $^

$(RELCYBERLIB): $(RELCYBEROBJS)
	$(CC) $(CFLAGS) $(DBGCFLAGS) $(LDFLAGS) -o $(RELCYBERLIB) $^
	mv $(RELCYBERLIB) $(RELDIR)/lib 
	mv $(RELLIB) $(RELDIR)/lib 
	mv $(RELINTERFACELIB) $(RELDIR)/lib 

$(RELBIN): $(RELBINOBJS)
	$(CC) $(CFLAGS) $(LDBINFLAGS) -o $(RELBIN) $^
	mv $(RELBIN) $(RELDIR)/bin

$(RELDIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $(RELCFLAGS) -o $@ $<

$(RELDIR)/%.o: $(CCI_DIR)/%.c
	$(CC) -c $(CFLAGS) $(RELCFLAGS) -o $@ $<

$(RELDIR)/%.o: $(CCI_DIR)/cyber/%.c
	$(CC) -c $(CFLAGS) $(RELCFLAGS) -o $@ $<

$(RELDIR)/%.o: $(SRC_DIR)test/%.c
	$(CC) -c $(CFLAGS) $(DBGCFLAGS) -o $@ $<

#
# other rules
#
service:  $(DBGMINIRUNKAFKA) $(RELMINIRUNKAFKA) $(DBGSERVICELIB) $(RELSERVICELIB)

$(DBGSERVICELIB): $(DBGSERVICEOBJS)
	echo $(DBGSERVICELIB)
	$(CC) $(CFLAGS) $(DBGCFLAGS) $(LDSERVICEFLAGS) -o $(DBGSERVICELIB) $^
	mv $(DBGSERVICELIB) $(DBGDIR)/lib

$(DBGMINIRUNKAFKA): $(DBGMINIRUNBINOBJS)
	$(CC) $(CFLAGS) $(DBGCFLAGS) $(LDBINFLAGS) -o $(DBGMINIRUNKAFKA) $^
	mv $(DBGMINIRUNKAFKA) $(DBGDIR)/bin

$(DBGDIR)/%.o: $(CCI_DIR)/service/%.c
	$(CC) -c $(CFLAGS) $(DBGCFLAGS) -o $@ $<

$(DBGDIR)/%.o: $(CCI_DIR)/fuser/%.c
	$(CC) -c $(CFLAGS) $(DBGCFLAGS) -o $@ $<

$(DBGDIR)/%.o: $(CCI_DIR)/mini-run/%.c
	$(CC) -c $(CFLAGS) $(DBGCFLAGS) -o $@ $<

#run
$(RELSERVICELIB): $(RELSERVICEOBJS)
	$(CC) $(CFLAGS) $(DBGCFLAGS) $(LDSERVICEFLAGS) -o $(RELSERVICELIB) $^
	mv $(RELSERVICELIB) $(RELDIR)/lib

$(RELMINIRUNKAFKA): $(RELMINIRUNBINOBJS)
	$(CC) $(CFLAGS) $(LDBINFLAGS) -o $(RELMINIRUNKAFKA) $^
	mv $(RELMINIRUNKAFKA) $(RELDIR)/bin

$(RELDIR)/%.o: $(CCI_DIR)/service/%.c
	$(CC) -c $(CFLAGS) $(RELCFLAGS) -o $@ $<

$(RELDIR)/%.o: $(CCI_DIR)/fuser/%.c
	$(CC) -c $(CFLAGS) $(RELCFLAGS) -o $@ $<

$(RELDIR)/%.o: $(CCI_DIR)/mini-run/%.c
	$(CC) -c $(CFLAGS) $(RELFLAGS) -o $@ $<

#trace

prep:
	@mkdir -p $(DBGDIR) $(RELDIR) $(DBGDIR)/lib $(DBGDIR)/bin $(RELDIR)/lib $(RELDIR)/bin

remake: clean all

tree:
	@tree -h

clean:
	rm -f $(RELOBJS) $(DBGOBJS) $(DBGBINOBJS) $(DBGINTERFACEOBJS) \
		  $(DBGDIR)/bin/* $(DBGDIR)/lib/* \
		  $(RELLIB) $(RELINTERFACEOBJS) $(RELDIR)/lib/*  \
		  $(RELBINOBJS) $(DBGCYBEROBJS) $(RELCYBEROBJS) \
		  $(RELDIR)/bin/* $(DBGDIR)/*.out $(DBGSERVICEOBJS) $(RELSERVICEOBJS) \
		  $(DBGMINIRUNBINOBJS)  $(RELMINIRUNBINOBJS)

	@tree -h 


		


