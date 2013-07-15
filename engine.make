# makefile

ifndef verbose
	SILENT = @
endif

ifdef clang
	CXX = clang++
else 
	CXX = g++
endif

ifndef config
	config = debug
endif

TARGETDIR = bin

ifeq ($(config),debug)
	OBJDIR 		= obj/debug
	TARGET 		= $(TARGETDIR)/program_debug.debug
	DEFINES 	= -DDEBUG
	INCLUDES   += -Ithirdparty/stb_image -I/opt/local/include
	COMPILER	= -std=c++11
	CPPFLAGS   += -MMD -MP $(DEFINES) -g -Wall $(INCLUDES) $(COMPILER)
	CXXFLAGS 	= $(CPPFLAGS)
	LDFLAGS 	= 
	LIBS       += -lGL -lglfw -lGLEW -lassimp
endif

ifeq ($(config),release)
	OBJDIR 		= obj/release
	TARGET 		= $(TARGETDIR)/program_debug.release
	DEFINES 	= -DNDEBUG
	INCLUDES   += -Ithirdparty/stb_image -I/opt/local/include
	COMPILER	= -std=c++11
	CPPFLAGS   += -MMD -MP $(DEFINES) -02 -Wall $(COMPILER)
	CXXFLAGS 	= $(CPPFLAGS)
	LDFLAGS 	= -s
	LIBS       += -lGL -lglfw -lGLEW -lassimp
endif

OBJECTS := \
	$(OBJDIR)/main.o \
	$(OBJDIR)/Program.o \
	$(OBJDIR)/Shader.o \
	$(OBJDIR)/Texture.o \
	$(OBJDIR)/Bitmap.o \
	$(OBJDIR)/Camera.o \
	$(OBJDIR)/Entity.o \
	$(OBJDIR)/Component.o \
	$(OBJDIR)/DrawComponent.o \
	$(OBJDIR)/CameraComponent.o \
	$(OBJDIR)/LightComponent.o \
	$(OBJDIR)/GraphicsManager.o \
	$(OBJDIR)/InputManager.o \
	$(OBJDIR)/Asset.o \
	$(OBJDIR)/Engine.o \
	$(OBJDIR)/util.o \

.PHONY: clean

all: $(TARGETDIR) $(OBJDIR) ${TARGET}

$(TARGET): $(TARGETDIR) $(OBJDIR) $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS) $(LIBS) $(LDFLAGS)

$(OBJDIR):
	@echo "Creating $(OBJDIR)"
	$(SILENT) mkdir -p $(OBJDIR)

$(TARGETDIR):
	@echo "Creating $(TARGETDIR)"
	$(SILENT) mkdir -p $(TARGETDIR)

clean:
	@echo "Cleaning program"
	$(SILENT) rm -f $(TARGET)
	$(SILENT) rm -rf $(OBJDIR)
	
run: ${TARGET}
	./${TARGET}

# Source Folders
AI_FOLDER 		= src/AI
GAME_FOLDER 	= src/Game 
INPUT_FOLDER 	= src/Input 
PHYSICS_FOLDER 	= src/Physics 
RENDERER_FOLDER = src/Renderer 
RESOURCE_FOLDER = src/Resource
UTIL_FOLDER		= src/Util

# ----------------------- Compile AI Folder --------------------------------- #

$(OBJDIR)/AIManager.o: $(AI_FOLDER)/AIManager.cpp 
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/AIComponent.o: $(AI_FOLDER)/AIComponent.cpp 
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/Algorithm.o: $(AI_FOLDER)/Algorithm.cpp 
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/AlgorithmFactory.o: $(AI_FOLDER)/AlgorithmFactory.cpp 
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/RotateAlg.o: $(AI_FOLDER)/RotateAlg.cpp 
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

# ----------------------- Compile Game Folder ------------------------------- #

$(OBJDIR)/main.o: $(GAME_FOLDER)/main.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/Engine.o: $(GAME_FOLDER)/Engine.cpp 
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/Entity.o: $(GAME_FOLDER)/Entity.cpp  
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/Component.o: $(GAME_FOLDER)/Component.cpp 
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/ComponentFactory.o: $(GAME_FOLDER)/ComponentFactory.cpp 
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

# ----------------------- Compile Input Folder ------------------------------ #

$(OBJDIR)/InputManager.o: $(INPUT_FOLDER)/InputManager.cpp 
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

# ----------------------- Compile Physics Folder ---------------------------- #

# ----------------------- Compile Renderer Folder --------------------------- #

$(OBJDIR)/DrawComponent.o: $(RENDERER_FOLDER)/DrawComponent.cpp 
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/CameraComponent.o: $(RENDERER_FOLDER)/CameraComponent.cpp 
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/LightComponent.o: $(RENDERER_FOLDER)/LightComponent.cpp 
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/GraphicsManager.o: $(RENDERER_FOLDER)/GraphicsManager.cpp 
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/Asset.o: $(RENDERER_FOLDER)/ModelAsset.cpp  
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/Program.o: $(RENDERER_FOLDER)/Program.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/Shader.o: $(RENDERER_FOLDER)/Shader.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/Texture.o: $(RENDERER_FOLDER)/Texture.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/Bitmap.o: $(RENDERER_FOLDER)/Bitmap.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

$(OBJDIR)/Camera.o: $(RENDERER_FOLDER)/Camera.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

# ----------------------- Compile Resource Folder --------------------------- #

$(OBJDIR)/ResourceManager.o: $(RESOURCE_FOLDER)/ResourceManager.cpp 
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

# ----------------------- Compile Util Folder ------------------------------- #

$(OBJDIR)/util.o: $(UTIL_FOLDER)/util.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

# ----------------------- End of stuff -------------------------------------- #

-include $(OBJECTS:%.o=%.d)