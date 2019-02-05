/*
-----------------------------------------------------------------------------
This source file is part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org

Copyright (c) 2000-2014 Torus Knot Software Ltd
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/
#ifndef _ShaderProgramFunction_
#define _ShaderProgramFunction_

#include "OgreShaderPrerequisites.h"
#include "OgreShaderParameter.h"
#include "OgreShaderFunctionAtom.h"

namespace Ogre {
namespace RTShader {

/** \addtogroup Optional
*  @{
*/
/** \addtogroup RTShader
*  @{
*/

/// represents a @ref FFPShaderStage, part of a Function
class _OgreRTSSExport FunctionStageRef
{
    friend class Function;
public:
    /** call a library function
     * @param name the function name
     */
    void callFunction(const char* name, const InOut& inout) const;

    /// @overload
    void callFunction(const char* name, const std::vector<Operand>& params) const;
    /// @overload
    void callFunction(const char* name, const In& arg, const Out& ret) const { callFunction(name, {arg, ret}); }
    /// @overload
    void callFunction(const char* name, const In& arg0, const In& arg1, const Out& ret) const
    {
        callFunction(name, {arg0, arg1, ret});
    }

    /// dst = texture(sampler, texcoord);
    void sampleTexture(const In& sampler, const In& texcoord, const Out& dst) const
    {
        sampleTexture({sampler, texcoord, dst});
    }
    /// @overload
    void sampleTexture(const std::vector<Operand>& params) const;

    /// to = from;
    void assign(const In& from, const Out& to) const { assign({from, to}); }
    /// @overload
    void assign(const std::vector<Operand>& params) const;
private:
    size_t mStage;
    Function* mParent;
    FunctionStageRef(size_t stage, Function* parent) : mStage(stage), mParent(parent) {}
};

/** A class that represents a shader based program function.
*/
class _OgreRTSSExport Function : public RTShaderSystemAlloc
{
    friend ProgramManager;
// Interface.
public:
    enum FunctionType
    {
        // internal function (default)
        FFT_INTERNAL,
        // Vertex program main
        FFT_VS_MAIN,
        // Pixel shader main
        FFT_PS_MAIN
    };

    /** Get the name of this function */
    const String& getName() const { return mName; }

    /** Get the description of this function */
    const String& getDescription() const { return mDescription; }

    /// @deprecated
    ParameterPtr resolveInputParameter(Parameter::Semantic semantic, int index,  const Parameter::Content content, GpuConstantType type);

    /** Resolve input parameter of this function
    @param content The content of the parameter.
    @param type The type of the desired parameter.
    @return parameter instance in case of that resolve operation succeeded.
    */
    ParameterPtr resolveInputParameter(Parameter::Content content, GpuConstantType type = GCT_UNKNOWN)
    {
        return resolveInputParameter(Parameter::SPS_UNKNOWN, 0, content, type);
    }

    /// resolve input parameter from previous output
    ParameterPtr resolveInputParameter(const ParameterPtr& out)
    {
        OgreAssert(out, "parameter must not be NULL");
        return resolveInputParameter(out->getSemantic(), out->getIndex(), out->getContent(), out->getType());
    }

    /**
     * get input parameter by content
     * @param content
     * @return parameter or NULL if not found
     */
    ParameterPtr getInputParameter(Parameter::Content content, GpuConstantType type = GCT_UNKNOWN)
    {
        return _getParameterByContent(mInputParameters, content, type);
    }

    /// @deprecated
    ParameterPtr resolveOutputParameter(Parameter::Semantic semantic, int index,  const Parameter::Content content, GpuConstantType type);

    /** Resolve output parameter of this function
    @param content The content of the parameter.
    @param type The type of the desired parameter.
    @return parameter instance in case of that resolve operation succeeded.
    */
    ParameterPtr resolveOutputParameter(Parameter::Content content, GpuConstantType type = GCT_UNKNOWN)
    {
        return resolveOutputParameter(Parameter::SPS_UNKNOWN, 0, content, type);
    }

    /**
     * get output parameter by content
     * @param content
     * @return parameter or NULL if not found
     */
    ParameterPtr getOutputParameter(Parameter::Content content, GpuConstantType type = GCT_UNKNOWN)
    {
        return _getParameterByContent(mOutputParameters, content, type);
    }

    /// @deprecated local parameters do not have index or sematic. use resolveLocalParameter(const String&, GpuConstantType)
    ParameterPtr resolveLocalParameter(Parameter::Semantic semantic, int index, const String& name, GpuConstantType type);

    /** Resolve local parameter of this function    
    @param name The name of the parameter.
    @param type The type of the desired parameter.  
    Return parameter instance in case of that resolve operation succeeded.
    */
    ParameterPtr resolveLocalParameter(const String& name, GpuConstantType type)
    {
        return resolveLocalParameter(Parameter::SPS_UNKNOWN, 0, name, type);
    }

    /// @deprecated local parameters do not have index or sematic. use resolveLocalParameter(const String&, GpuConstantType)
    ParameterPtr resolveLocalParameter(Parameter::Semantic semantic, int index, const Parameter::Content content, GpuConstantType type);

    /** Resolve local parameter of this function
    @param content The content of the parameter.
    @param type The type of the desired parameter.
    Return parameter instance in case of that resolve operation succeeded.
    */
    ParameterPtr resolveLocalParameter(Parameter::Content content, GpuConstantType type = GCT_UNKNOWN)
    {
        return resolveLocalParameter(Parameter::SPS_UNKNOWN, 0,content, type);
    }

    /**
     * get local parameter by content
     * @param content
     * @return parameter or NULL if not found
     */
    ParameterPtr getLocalParameter(Parameter::Content content)
    {
        return _getParameterByContent(mLocalParameters, content, GCT_UNKNOWN);
    }
    /// @overload
    ParameterPtr getLocalParameter(const String& name)
    {
        return _getParameterByName(mLocalParameters, name);
    }

    /// @deprecated do not use
    OGRE_DEPRECATED static ParameterPtr getParameterByName(const ShaderParameterList& parameterList, const String& name)
    {
        return _getParameterByName(parameterList, name);
    }
    /// @deprecated do not use
    OGRE_DEPRECATED static ParameterPtr getParameterBySemantic(const ShaderParameterList& parameterList, const Parameter::Semantic semantic, int index)
    {
        return _getParameterBySemantic(parameterList, semantic, index);
    }
    /// @deprecated use getInputParameter / getOutputParameter / getLocalParameter instead
    OGRE_DEPRECATED static ParameterPtr getParameterByContent(const ShaderParameterList& parameterList, const Parameter::Content content, GpuConstantType type)
    {
        return _getParameterByContent(parameterList, content, type);
    }

    /** Return a list of input parameters. */
    const ShaderParameterList& getInputParameters() const { return mInputParameters; }  

    /** Return a list of output parameters. */
    const ShaderParameterList& getOutputParameters() const { return mOutputParameters; }

    /** Return a list of local parameters. */
    const ShaderParameterList& getLocalParameters() const { return mLocalParameters; }  
    
    /** Add a function atom instance to this function. 
    @param atomInstance The atom instance to add.
    */
    void addAtomInstance(FunctionAtom* atomInstance);

    /// @deprecated use FunctionStageRef::assign instead
    OGRE_DEPRECATED void addAtomAssign(ParameterPtr lhs, ParameterPtr rhs, int groupOrder);

    /// get a @ref FFPShaderStage of this function
    FunctionStageRef getStage(size_t s)
    {
        return FunctionStageRef(s, this);
    }

    /** Delete a function atom instance from this function. 
    @param atomInstance The atom instance to OGRE_DELETE.
    */
    bool deleteAtomInstance(FunctionAtom* atomInstance);

    /** Return list of atom instances composing this function. (Const version) */
    const FunctionAtomInstanceList& getAtomInstances();

    /** Add input parameter to this function. */
    void addInputParameter(ParameterPtr parameter);

    /** Add output parameter to this function. */
    void addOutputParameter(ParameterPtr parameter);

    /** Delete input parameter from this function. */
    void deleteInputParameter(ParameterPtr parameter);

    /** Delete output parameter from this function. */
    void deleteOutputParameter(ParameterPtr parameter);

    /** Delete all input parameters from this function. */
    void deleteAllInputParameters();

    /** Delete all output parameters from this function. */
    void deleteAllOutputParameters();

    /** get function type. */
    FunctionType getFunctionType() const;


protected:

    static ParameterPtr _getParameterByName(const ShaderParameterList& parameterList, const String& name);
    static ParameterPtr _getParameterBySemantic(const ShaderParameterList& parameterList, const Parameter::Semantic semantic, int index);
    static ParameterPtr _getParameterByContent(const ShaderParameterList& parameterList, const Parameter::Content content, GpuConstantType type);


    /** Class constructor.
    @param name The name of this function.
    @param desc The description of this function.
    @remarks This class is allocated via an instance of Program class. 
    */
    Function(const String& name, const String& desc, const FunctionType functionType);

    /** Class destructor */
    ~Function();

    /** Add parameter to given list */
    void addParameter(ShaderParameterList& parameterList, ParameterPtr parameter);

    /** Delete parameter from a given list */
    void deleteParameter(ShaderParameterList& parameterList, ParameterPtr parameter);

protected:
    // Function name.
    String mName;
    // Function description.
    String mDescription;
    // Input parameters.
    ShaderParameterList mInputParameters;
    // Output parameters.
    ShaderParameterList mOutputParameters;
    // Local parameters.
    ShaderParameterList mLocalParameters;
    // Atom instances composing this function.
    std::map<size_t, FunctionAtomInstanceList> mAtomInstances;
    FunctionAtomInstanceList mSortedAtomInstances;
    // Function type
    FunctionType mFunctionType;
    
private:
    friend class Program;
};

typedef std::vector<Function*>                     ShaderFunctionList;
typedef ShaderFunctionList::iterator                ShaderFunctionIterator;
typedef ShaderFunctionList::const_iterator          ShaderFunctionConstIterator;

/** @} */
/** @} */

}
}

#endif
