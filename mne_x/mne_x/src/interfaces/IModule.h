//=============================================================================================================
/**
* @file     IModule.h
* @author   Christoph Dinh <chdinh@nmr.mgh.harvard.edu>;
*           Matti Hamalainen <msh@nmr.mgh.harvard.edu>
* @version  1.0
* @date     February, 2013
*
* @section  LICENSE
*
* Copyright (C) 2013, Christoph Dinh and Matti Hamalainen. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that
* the following conditions are met:
*     * Redistributions of source code must retain the above copyright notice, this list of conditions and the
*       following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
*       the following disclaimer in the documentation and/or other materials provided with the distribution.
*     * Neither the name of the Massachusetts General Hospital nor the names of its contributors may be used
*       to endorse or promote products derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL MASSACHUSETTS GENERAL HOSPITAL BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*
* @brief    Contains declaration of IModule interface class.
*
*/

#ifndef IMODULE_H
#define IMODULE_H


//*************************************************************************************************************
//=============================================================================================================
// QT INCLUDES
//=============================================================================================================

#include <QThread>
#include <QCoreApplication>




#include "../../MNE/rtMeas/Nomenclature/nomenclature.h" //ToDo this has not to be relative; //Interfaces needs to be moved to a separate lib



//*************************************************************************************************************
//=============================================================================================================
// DEFINE NAMESPACE MNEX
//=============================================================================================================

namespace MNEX
{


//*************************************************************************************************************
//=============================================================================================================
// ENUMERATIONS
//=============================================================================================================

//=============================================================================================================
/**
* Module Type enumeration.
*/
enum Type
{
    _ISensor,				/**< Type for a sensor module. */
    _IRTAlgorithm,			/**< Type for a real-time algorithm module. */
    _IRTRecord,				/**< Type for a real-time record module. */
    _IAlert,				/**< Type for a alert module. */
    _IRTVisualization		/**< Type for a real-time visualization module. */
};

using namespace RTMEASLIB;


//=========================================================================================================
/**
* DECLARE CLASS IModule
*
* @brief The IModule class is the base interface class of all modules.
*/
class IModule : public QThread
{

public:

    //=========================================================================================================
    /**
    * Destroys the IModule.
    */
    virtual ~IModule() {};

    //=========================================================================================================
    /**
    * Starts the IModule.
    * Pure virtual method.
    *
    * @return true if success, false otherwise
    */
    virtual bool start() = 0;// = 0 call is not longer possible - it has to be reimplemented in child;

    //=========================================================================================================
    /**
    * Stops the IModule.
    * Pure virtual method.
    *
    * @return true if success, false otherwise
    */
    virtual bool stop() = 0;

    //=========================================================================================================
    /**
    * Returns the provider id
    *
    * @return the provider id (Module ID).
    */
    inline MDL_ID::Module_ID getModule_ID() const;

    //=========================================================================================================
    /**
    * Returns the module type.
    * Pure virtual method.
    *
    * @return type of the IModule
    */
    virtual Type getType() const = 0;

    //=========================================================================================================
    /**
    * Returns the module name.
    * Pure virtual method.
    *
    * @return the name of module.
    */
    virtual const char* getName() const = 0;

    //=========================================================================================================
    /**
    * Returns the set up widget for configuration of the IModule.
    * Pure virtual method.
    *
    * @return the setup widget.
    */
    virtual QWidget* setupWidget() = 0; //setup()

    //=========================================================================================================
    /**
    * Returns the widget which is shown under configuration tab while running mode.
    * Pure virtual method.
    *
    * @return the run widget.
    */
    virtual QWidget* runWidget() = 0;

    //=========================================================================================================
    /**
    * Sets the activation status of the module.
    *
    * @param [in] status the new activation status of the module.
    */
    inline void setStatus(bool status);

    //=========================================================================================================
    /**
    * Returns the activation status of the module.
    *
    * @return true if module is activated.
    */
    inline bool isActive() const;

protected:

    //=========================================================================================================
    /**
    * The starting point for the thread. After calling start(), the newly created thread calls this function.
    * Returning from this method will end the execution of the thread.
    * Pure virtual method inherited by QThread
    */
    virtual void run() = 0;

    MDL_ID::Module_ID m_MDL_ID;     /**< Holds the module id.*/

private:

    bool m_bStatus;                 /**< Holds the activation status. */
};

//*************************************************************************************************************
//=============================================================================================================
// INLINE DEFINITIONS
//=============================================================================================================

inline MDL_ID::Module_ID IModule::getModule_ID() const
{
    return m_MDL_ID;
}


//*************************************************************************************************************

inline void IModule::setStatus(bool status)
{
    m_bStatus = status;
}


//*************************************************************************************************************

inline bool IModule::isActive() const
{
    return m_bStatus;
}



} //Namespace

Q_DECLARE_INTERFACE(MNEX::IModule, "csa_rt/1.0")

#endif //IMODULE_H