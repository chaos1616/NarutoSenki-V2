#pragma once

// Protected reference property

#define PPROP(varType, varName, funName)              \
private:                                              \
	varType varName;                                  \
                                                      \
public:                                               \
	inline varType get##funName() { return varName; } \
	inline void set##funName(varType var) { varName = var; }

#define PROP(varType, varName, funName)               \
protected:                                            \
	varType varName;                                  \
                                                      \
public:                                               \
	inline varType get##funName() { return varName; } \
	inline void set##funName(varType var) { varName = var; }

#define PROP_REF(varType, varName, funName)                  \
protected:                                                   \
	varType varName;                                         \
                                                             \
public:                                                      \
	inline const varType &get##funName() { return varName; } \
	inline void set##funName(const varType &var) { varName = var; }

#define PROP_SREF(varType, varName, funName)           \
protected:                                             \
	varType varName;                                   \
                                                       \
public:                                                \
	inline varType &get##funName() { return varName; } \
	inline void set##funName(const varType &var) { varName = var; }

#define PROP_Vector(varType, varName, funName) PROP_SREF(varType, varName, funName)

// Protected virtual reference property

#define VPPROP(varType, varName, funName)                     \
private:                                                      \
	varType varName;                                          \
                                                              \
public:                                                       \
	inline virtual varType get##funName() { return varName; } \
	inline virtual void set##funName(varType var) { varName = var; }

#define VPROP(varType, varName, funName)                      \
protected:                                                    \
	varType varName;                                          \
                                                              \
public:                                                       \
	inline virtual varType get##funName() { return varName; } \
	inline virtual void set##funName(varType var) { varName = var; }

#define VPROP_REF(varType, varName, funName)                         \
protected:                                                           \
	varType varName;                                                 \
                                                                     \
public:                                                              \
	inline virtual const varType &get##funName() { return varName; } \
	inline virtual void set##funName(const varType &var) { varName = var; }

// cocos2d::Value Type Property

#define PROP_String(varName, funName)                                \
private:                                                             \
	Value varName;                                                   \
                                                                     \
public:                                                              \
	inline std::string get##funName() { return varName.asString(); } \
	inline const Value &get##funName##_Value() { return varName; }   \
	inline void set##funName(const char *var) { varName = var; }     \
	inline void set##funName(const std::string &var) { varName = var; }

#define PROP_Bool(varName, funName)                                \
private:                                                           \
	Value varName;                                                 \
                                                                   \
public:                                                            \
	inline int get##funName() { return varName.asBool(); }         \
	inline const Value &get##funName##_Value() { return varName; } \
	inline void set##funName(int var) { varName = var; }

#define PROP_Int(varName, funName)                                 \
private:                                                           \
	Value varName;                                                 \
                                                                   \
public:                                                            \
	inline int get##funName() { return varName.asInt(); }          \
	inline const Value &get##funName##_Value() { return varName; } \
	inline void set##funName(int var) { varName = var; }

#define PROP_UInt8(varName, funName)                                 \
private:                                                             \
	Value varName;                                                   \
                                                                     \
public:                                                              \
	inline unsigned char get##funName() { return varName.asByte(); } \
	inline const Value &get##funName##_Value() { return varName; }   \
	inline void set##funName(unsigned char var) { varName = var; }

#define PROP_UInt32(varName, funName)                              \
private:                                                           \
	Value varName;                                                 \
                                                                   \
public:                                                            \
	inline unsigned int get##funName() { return varName.asInt(); } \
	inline const Value &get##funName##_Value() { return varName; } \
	inline void set##funName(unsigned int var) { varName = var; }

#define PROP_Float(varName, funName)                               \
private:                                                           \
	Value varName;                                                 \
                                                                   \
public:                                                            \
	inline float get##funName() { return varName.asFloat(); }      \
	inline const Value &get##funName##_Value() { return varName; } \
	inline void set##funName(float var) { varName = var; }

#define PROP_Double(varName, funName)                              \
private:                                                           \
	Value varName;                                                 \
                                                                   \
public:                                                            \
	inline double get##funName() { return varName.asDouble(); }    \
	inline const Value &get##funName##_Value() { return varName; } \
	inline void set##funName(double var) { varName = var; }

// Cocos Extensions

#define CC_SYNTHESIZE_RETAIN_SET_ONLY(varType, varName, funName) \
private:                                                         \
	varType varName;                                             \
                                                                 \
public:                                                          \
	inline virtual void set##funName(varType var)                \
	{                                                            \
		if (varName != var)                                      \
		{                                                        \
			CC_SAFE_RETAIN(var);                                 \
			CC_SAFE_RELEASE(varName);                            \
			varName = var;                                       \
		}                                                        \
	}
