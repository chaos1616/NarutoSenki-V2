EXECUTABLE = HelloCpp

COCOS_ROOT = /home/re/Tools/cocos2d-x/cocos2d-x-2.2.6

INCLUDES = -I.. -I../Classes \
	-I$(COCOS_ROOT)/external \
	-I$(COCOS_ROOT)/external/chipmunk/include/chipmunk \
	-I$(COCOS_ROOT)/CocosDenshion/include \
	-I.. \
	-I../CCBReader \
	-I../GUI/CCControlExtension \
	-I../GUI/CCEditBox \
	-I../network \
	-I../CocoStudio/Armature \
	-I../CocoStudio/Components \
	-I../CocoStudio/GUI \
	-I../CocoStudio/Json \
	-I../CocoStudio/Reader \
	-I../platform/third_party/linux/libfreetype2 \
	-I../../extensions \
	-I../../extensions/CCBReader \
	-I../../extensions/GUI/CCControlExtension \
	-I../../extensions/GUI/CCControlExtension \
	-I../../external/chipmunk/include/chipmunk \
	-I../../extensions/network \
	-I../../extensions/Components \

SOURCES = main.cpp \
        ../Classes/AppDelegate.cpp

include $(COCOS_ROOT)/cocos2dx/proj.linux/cocos2dx.mk

SHAREDLIBS += -lcocos2d
COCOS_LIBS = $(LIB_DIR)/libcocos2d.so

$(TARGET): $(OBJECTS) $(STATICLIBS) $(COCOS_LIBS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_LINK)$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(SHAREDLIBS) $(STATICLIBS)

$(OBJ_DIR)/%.o: %.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -g -c $< -o $@

$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -g -c $< -o $@
