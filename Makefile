CXX = g++

SRCDIR=./
CCFILES += \
		$(SRCDIR)/base_hog_svm.c \
		$(SRCDIR)/det_main.c \
		$(SRCDIR)/vec.c \

HFILES += \
		$(SRCDIR)/det_main.h \
		$(SRCDIR)/vec.h \
		$(SRCDIR)/base_hog_svm.h \


LD_FLAGS         = -lm 

LD_LIBS          = 

OBJS             += $(patsubst %.c,%.c.o, $(CCFILES))

CFLAGS           =  -g -O0 -m64 -Wall

EXECUTABLE       = iHog

INCLUDE_FLAGS    = -I$(SRCDIR) -I$(COMMDIR) -I$(NSDIR) -I$(AGCDIR) -I$(VADDIR)
#INCLUDE_FLAGS    = -I$(SRCDIR) -I$(COMMDIR) -I$(AGCDIR) -I$(VADDIR)

## Each subdirectory must supply rules for building sources it contributes
all: $(OBJS) $(CCFILES)
	$(CXX) -o $(EXECUTABLE) $(CFLAGS) $(OBJS) $(LD_FLAGS) 


$(OBJS): $(CCFILES) $(HFILES)
	$(CXX) $(CFLAGS) $(INCLUDE_FLAGS) -o $@ -c $*


.phony: clean


clean:
	@rm -f $(OBJS) $(EXECUTABLE)
