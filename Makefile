########################################################################
####################### Makefile Template ##############################
########################################################################

# Makefile settings - Can be customized.
APPNAME_MAIN = DFM
APPNAME_VISUALS = Visualization
EXT = .cpp
SRCDIR = content
OBJDIR = obj
DEPDIR = dep

# Compiler settings - Can be customized.
CC = g++
CXXFLAGS = -std=c++17 -Wall -g -O0 -I./$(SRCDIR)
LDFLAGS = -lSDL2

############## Do not change anything from here downwards! #############
SRC = $(shell find $(SRCDIR) -name '*$(EXT)') # Find all .cpp files recursively
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)  # Replace .cpp with .o
DEP = $(SRC:$(SRCDIR)/%$(EXT)=$(DEPDIR)/%.d)  # Replace .cpp with .d

# UNIX-based OS variables & settings
RM = rm -f        # Use -f to avoid errors when file does not exist
DELOBJ = $(OBJ)
DELDEP = $(DEP)

# Windows OS variables & settings
DEL = del
EXE = .exe
WDELOBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)\\%.o)
WDELDEP = $(SRC:$(SRCDIR)/%$(EXT)=$(DEPDIR)\\%.d)

########################################################################
####################### Targets beginning here #########################
########################################################################

all: $(APPNAME_MAIN) $(APPNAME_VISUALS)

# Builds the app for the main.cpp (DFM_MAIN)
$(APPNAME_MAIN): $(OBJDIR)/main.o $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $(OBJDIR)/main.o $(filter-out $(OBJDIR)/visuals.o, $(OBJ)) $(LDFLAGS)

# Builds the app for the visuals.cpp (DFM_VISUALS)
$(APPNAME_VISUALS): $(OBJDIR)/visuals.o $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $(OBJDIR)/visuals.o $(filter-out $(OBJDIR)/main.o, $(OBJ)) $(LDFLAGS)

# Create the obj and dep directories if they don't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(DEPDIR):
	mkdir -p $(DEPDIR)

# Rule to compile object files for main.cpp (for DFM_MAIN) from the root directory
$(OBJDIR)/main.o: main.cpp
	@mkdir -p $(dir $@)    # Ensure directory exists
	$(CC) $(CXXFLAGS) -o $@ -c $<

# Rule to compile object files for visuals.cpp (for DFM_VISUALS) from the root directory
$(OBJDIR)/visuals.o: visuals.cpp
	@mkdir -p $(dir $@)    # Ensure directory exists
	$(CC) $(CXXFLAGS) -o $@ -c $<

# Rule to compile other common object files (excluding main.cpp and visuals.cpp)
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	@mkdir -p $(dir $@)    # Ensure directory exists
	$(CC) $(CXXFLAGS) -o $@ -c $<

$(DEPDIR)/%.d: $(SRCDIR)/%$(EXT)
	@mkdir -p $(dir $@)    # Ensure directory exists
	@$(CPP) $(CXXFLAGS) $< -MM -MT $(@:$(DEPDIR)/%.d=$(OBJDIR)/%.o) >$@

# Includes all .h files
-include $(DEP)

# Rule to compile and run the app for the main executable (DFM_MAIN)
.PHONY: run
run: $(APPNAME_MAIN)
	./$(APPNAME_MAIN)

# Rule to compile and run the app for the visuals executable (DFM_VISUALS)
.PHONY: visual
visual: $(APPNAME_VISUALS)
	./$(APPNAME_VISUALS)

################### Cleaning rules for Unix-based OS ###################
# Cleans complete project
.PHONY: clean
clean:
	$(RM) $(DELOBJ) $(DELDEP) $(APPNAME_MAIN) $(APPNAME_VISUALS)

# Cleans only all files with the extension .d
.PHONY: cleandep
cleandep:
	$(RM) $(DELDEP)

#################### Cleaning rules for Windows OS #####################
# Cleans complete project
.PHONY: cleanw
cleanw:
	$(DEL) $(WDELOBJ) $(WDELDEP) $(APPNAME_MAIN)$(EXE) $(APPNAME_VISUALS)$(EXE)

# Cleans only all files with the extension .d
.PHONY: cleandepw
cleandepw:
	$(DEL) $(WDELDEP)
