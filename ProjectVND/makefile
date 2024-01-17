CXX = g++
CXXFLAGS = -std=c++17
BITS_OPTION = -m64

SRCDIR = src
OBJDIR = obj

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

vnd: $(OBJS) 
	@echo  "\033[31m \nLinking all objects files: \033[0m"
	$(CXX) $(BITS_OPTION) $(OBJS) -o $@ $(CXXFLAGS)

-include $(OBJS:.o=.d)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo  "\033[31m \nCompiling $<: \033[0m"
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo  "\033[32m \ncreating $< dependency file: \033[0m"
	$(CXX) -std=c++0x  -MM $< > $(basename $@).d
	@mv -f $(basename $@).d $(basename $@).d.tmp
	@sed -e 's|.*:|$(basename $@).o:|' < $(basename $@).d.tmp > $(basename $@).d
	@rm -f $(basename $@).d.tmp

clean:
	@echo "\033[31mcleaning obj directory \033[0m"
	@rm vnd -f $(OBJDIR)/*.o $(OBJDIR)/*.d


rebuild: clean vnd
