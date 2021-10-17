#pragma once

// Protected reference property

#define PROP(varType, varName, funName)                \
protected:                                             \
	varType varName;                                   \
                                                       \
public:                                                \
	inline varType get##funName() { return varName; }; \
	inline void set##funName(varType var) { varName = var; };

#define PROP_REF(varType, varName, funName)                   \
protected:                                                    \
	varType varName;                                          \
                                                              \
public:                                                       \
	inline const varType &get##funName() { return varName; }; \
	inline void set##funName(const varType &var) { varName = var; };

#define PROP_SREF(varType, varName, funName)            \
protected:                                              \
	varType varName;                                    \
                                                        \
public:                                                 \
	inline varType &get##funName() { return varName; }; \
	inline void set##funName(const varType &var) { varName = var; };

// Protected virtual reference property

#define VPROP(varType, varName, funName)                       \
protected:                                                     \
	varType varName;                                           \
                                                               \
public:                                                        \
	inline virtual varType get##funName() { return varName; }; \
	inline virtual void set##funName(varType var) { varName = var; };

#define VPROP_REF(varType, varName, funName)                          \
protected:                                                            \
	varType varName;                                                  \
                                                                      \
public:                                                               \
	inline virtual const varType &get##funName() { return varName; }; \
	inline virtual void set##funName(const varType &var) { varName = var; };

// Private property

#define PPROP(varType, varName, funName)               \
private:                                               \
	varType varName;                                   \
                                                       \
public:                                                \
	inline varType get##funName() { return varName; }; \
	inline void set##funName(varType var) { varName = var; };

// Private virtual property

#define VPPROP(varType, varName, funName)                      \
private:                                                       \
	varType varName;                                           \
                                                               \
public:                                                        \
	inline virtual varType get##funName() { return varName; }; \
	inline virtual void set##funName(varType var) { varName = var; };

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
