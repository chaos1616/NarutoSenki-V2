EXECUTABLE = NarutoSenki

SOURCES = main.cpp \
	../Classes/AppDelegate.cpp \
	../Classes/ActionButton.cpp \
	../Classes/CharacterBase.cpp \
	../Classes/BGLayer.cpp \
	../Classes/CreditsLayer.cpp \
	../Classes/Effect.cpp \
	../Classes/Element.cpp \
	../Classes/GameLayer.cpp \
	../Classes/GameOver.cpp \
	../Classes/GameScene.cpp \
	../Classes/GearLayer.cpp \
	../Classes/HPBar.cpp \
	../Classes/HudLayer.cpp \
	../Classes/JoyStick.cpp \
	../Classes/LoadLayer.cpp \
	../Classes/NetworkLayer.cpp \
	../Classes/PauseLayer.cpp \
	../Classes/RankingLayer.cpp \
	../Classes/SelectLayer.cpp \
	../Classes/SkillLayer.cpp \
	../Classes/StartMenu.cpp \
	../Classes/MyUtils/CCScrewLayer.cpp \
	../Classes/MyUtils/CCShake.cpp \
	../Classes/MyUtils/CCStrokeLabel.cpp \
	../Classes/MyUtils/KTools.cpp \
	../Classes/MyUtils/MD5ChecksumDefines.cpp \

SHAREDLIBS = -lcocos2d -lcocosdenshion -lcurl -lsqlite3 -llua
COCOS_LIBS = $(LIB_DIR)/libcocos2d.so $(LIB_DIR)/libcocosdenshion.so $(LIB_DIR)/liblua.so

include ../../../cocos2dx/proj.linux/cocos2dx.mk

INCLUDES +=	 -I../ \
	-I../../ \
	-I../Classes \
	-I$(COCOS_ROOT)/CocosDenshion/include \
	-I$(COCOS_ROOT)/extensions/ \
	-I$(COCOS_ROOT)/external/ \
	-I$(COCOS_ROOT)/external/chipmunk/include/chipmunk \
	-I$(COCOS_ROOT)/external/libwebsockets/linux \
	-I$(COCOS_ROOT)/scripting/lua/lua \
    -I$(COCOS_ROOT)/scripting/lua/tolua \
    -I$(COCOS_ROOT)/scripting/lua/cocos2dx_support \

STATICLIBS += \
	$(LIB_DIR)/libextension.a \
	$(LIB_DIR)/libbox2d.a \
	$(LIB_DIR)/libchipmunk.a \
	$(LIB_DIR)/libwebsockets.a \

####### Build rules
$(TARGET): $(OBJECTS) $(STATICLIBS) $(COCOS_LIBS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	@mkdir -p ../../../projects/NarutoSenki/__Bin__/Linux/Data
	cp -R -n ../../../projects/NarutoSenki/Resources/* 	../../../projects/NarutoSenki/__Bin__/Linux/Data
	cp -R -n ../../../projects/NarutoSenki/lua/* 		../../../projects/NarutoSenki/__Bin__/Linux/lua
	$(LOG_LINK)$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(STATICLIBS) $(SHAREDLIBS) $(LIBS)
	cp $(@D)/NarutoSenki ../../../projects/NarutoSenki/__Bin__/Linux

####### Compile
$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

$(OBJ_DIR)/%.o: %.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

$(OBJ_DIR)/%.o: %.c $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CC)$(CC) $(CCFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@
