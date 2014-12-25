/*=============================================================
  FILE:
    include/zz_SynthConfig.h

  AUTHOR:
    zimzum@github 

  DESCRIPTION:
    The definition of the zz_SynthConfig class - configuration
    class for the zz_synth library.
 
  License: GNU GPL v2.0 
  =============================================================*/

#ifndef _SYNTH_CONFIG_H_
#define _SYNTH_CONFIG_H_

class zz_SynthConfig
{
    private:
        zz_SynthConfig();
        zz_SynthConfig(zz_SynthConfig const& copy);
        zz_SynthConfig& operator=(zz_SynthConfig const& copy);

    public:
        static zz_SynthConfig& getInstance()
        {   
            // The only instance. Guaranteed to be lazy initialised and
            // destroyed correctly.
            static zz_SynthConfig instance;
            return instance;
        }
};

#endif /* _SYNTH_CONFIG_H_ */
