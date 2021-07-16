
from io import StringIO
import sys
import json
import os 
sys.path.insert(0, '/Users/tranxuan/Nextcloud/HDD/xuantran/Workspace/02_SW/MeshDevice/Integration/CodeGen')
from CodGenLib import cdlib_get_value, cdlib_push

dir_path = os.path.dirname(os.path.realpath(__file__))

def light_forward(conf_data):
    print("- light_forward:")
    if( not conf_data['Light']['ConfigSet'] ):
        print("Component is deactivated!\r\n")
    else:
        # print(" Pushed_data:")
        hwabdio_pushed_data = {'HwAbDio':{'ConfigSet':[]}}
        hwabpwm_pushed_data = {'HwAbPwm':{'ConfigSet':[]}}
        for signal in conf_data['Light']['ConfigSet']:
            # Brighness is enable 
            if (cdlib_get_value(signal['Brighness'],1,1)):
                signal_pushed_data = {'Signal': None}
                signal_pushed_data['Name']        = 'Light_' + signal['Name']
                signal_pushed_data['ConnectedTo'] = signal['ConnectedTo']
                signal_pushed_data['InitState']   = signal['InitState']
                signal_pushed_data['InitDuty']    = signal['InitDuty']
                hwabpwm_pushed_data['HwAbPwm']['ConfigSet'].append(signal_pushed_data)
            else:
                signal_pushed_data = {'Signal': None}
                signal_pushed_data['Name']        = 'Light_' + signal['Name']
                signal_pushed_data['ConnectedTo'] = signal['ConnectedTo']
                signal_pushed_data['InitState']   = signal['InitState']
                hwabdio_pushed_data['HwAbDio']['ConfigSet'].append(signal_pushed_data)
       
        conf_data = dict(cdlib_push(conf_data, hwabdio_pushed_data))
        conf_data = dict(cdlib_push(conf_data, hwabpwm_pushed_data))
    return conf_data

def generate_report(conf_data):
    report_content = ""
    report_content += "ConfigSet:\r\n"
    if( not conf_data['Light']['ConfigSet'] ):
        report_content = "Component is deactivated!\r\n"
    else:
        for signal in conf_data['Light']['ConfigSet']:
            report_content += "    Signal: Light_"+signal['Name']+"\r\n"
            report_content += "         ConnectedTo: "+ str(cdlib_get_value(signal['ConnectedTo'],1,1))+"\r\n"
            report_content += "         InitState : "+ str(cdlib_get_value(signal['InitState'],1,1))+"\r\n"
            if (cdlib_get_value(signal['Brighness'],1,1)):
                report_content += "         InitDuty  : "+ str(cdlib_get_value(signal['InitDuty'],1,1))+"\r\n"
            report_content += "         Brightness:  "+ str(cdlib_get_value(signal['Brighness'],1,1))+"\r\n"

    report_file = open(os.path.join(dir_path,"Light_Report.txt"), "w")
    report_file.write(report_content)
    report_file.close()

def generate_cfg_h(conf_data):
    cfg_ht_file = open(dir_path+"/Light_Cfg.ht","r")
    cfg_h_file_content = cfg_ht_file.read()
    cfg_h_setting = ""
    off_setting = "STD_OFF\r\n"
    on_setting  = "STD_ON\r\n"
    cfg_h_setting += "#define LIGHT_CFG_MODULE_ACTIVE   "
    if( not conf_data['Light']['ConfigSet'] ):
        print("Light component is disbaled")
        cfg_h_setting += off_setting
    else:
        cfg_h_setting += on_setting
        cfg_h_setting += "#define LIGHT_CFG_MQTT            "
        if(cdlib_get_value(conf_data['Light']['General']['MqttSupported'],1,1)):
             cfg_h_setting += on_setting
        else:
            cfg_h_setting  += off_setting
        cfg_h_setting += "#define LIGHT_CFG_DEBUG           "
        if(cdlib_get_value(conf_data['Light']['General']['DebugEnable'],1,1)):
            cfg_h_setting += on_setting
        else:
            cfg_h_setting += off_setting
        cfg_h_setting += "#define LIGHT_CFG_INFO            "
        if(cdlib_get_value(conf_data['Light']['General']['InfoEnable'],1,1)):
            cfg_h_setting += on_setting
        else:
            cfg_h_setting += off_setting
        
        cfg_h_setting += "#define LIGHT_TOGGLE_FILTER_TIME  " + cdlib_get_value(conf_data['Light']['General']['ToggleFilterTime'],1,1)+"\r\n"


        # number of signal
        cfg_h_setting += "#define LIGHT_CFG_NUM_LIGHTS      " + str(len(conf_data['Light']['ConfigSet'])) +'u'

        cfg_h_signals_id =""
        signal_id = 0
        for signal in conf_data['Light']['ConfigSet']:
            cfg_h_signals_id += "#define Light_"+signal['Name'] + "   " + str(signal_id)+"u\r\n"
            signal_id +=1

    cfg_h_file_content = cfg_h_file_content.replace("<CONFIGURATION SETTING>", cfg_h_setting)
    cfg_h_file_content = cfg_h_file_content.replace("<SIGNALS ID>", cfg_h_signals_id)
    cfg_h_file_content = cfg_h_file_content.replace("//<INCLUDE DRIVER>", "#include \"HwAbPwm.h\"\r\n"+"#include \"HwAbDio.h\"")
    cfg_ht_file.close()
    # generate the files
    cfg_h_file = open(os.path.join(dir_path,"Light_Cfg.h"), "w")
    cfg_h_file.write(cfg_h_file_content)
    cfg_h_file.close()
def generate_cfg_c(conf_data):
    cfg_ct_file = open(dir_path+"/Light_Cfg.ct","r")
    cfg_c_file_content = cfg_ct_file.read()
    cfg_c_signals = ""
    if( not conf_data['Light']['ConfigSet'] ):
        return
    else:
        for signal in conf_data['Light']['ConfigSet']:
            cmd_topic   = cdlib_get_value(conf_data['HassDevice']['General']['Name'],1,1)
            cmd_topic  += "/light/"
            cmd_topic  += signal['Name']
            state_topic = cmd_topic

            cmd_topic   += "/cmd"
            state_topic += "/st"

            cfg_c_signals += "  {\r\n"
            cfg_c_signals += "      //" + cdlib_get_value(signal['FriendlyName'],1,1) + "\r\n"
            cfg_c_signals += "      \"" + cdlib_get_value(signal['FriendlyName'],1,1) +"\",\r\n"
            cfg_c_signals += "      \"" + cmd_topic +"\",\r\n"
            cfg_c_signals += "      \"" + state_topic +"\",\r\n"
            cfg_c_signals += "      " + str(cdlib_get_value(signal['InitState'],1,1))+",\r\n"
            cfg_c_signals += "      " + str(cdlib_get_value(signal['ConnectedTo'],1,1)) +",\r\n"
            cfg_c_signals += "      " + str(cdlib_get_value(signal['Brighness'],1,1)) +",\r\n"
            if(cdlib_get_value(signal['Brighness'],1,1)):
                cfg_c_signals += "      HwAbPwm_Light_" + cdlib_get_value(signal['FriendlyName'],1,1) +",\r\n"
            else:
                cfg_c_signals += "      HwAbDio_Light_" + cdlib_get_value(signal['FriendlyName'],1,1) +",\r\n"
            cfg_c_signals += "  },\r\n"
    cfg_c_file_content = cfg_c_file_content.replace("<SIGNALS CONFIGURATION>", cfg_c_signals)
    cfg_ct_file.close()
    # generate the files
    cfg_c_file = open(os.path.join(dir_path,"Light_Cfg.c"), "w")
    cfg_c_file.write(cfg_c_file_content)
    cfg_c_file.close()


def light_generate(conf_data):
    print("- light_generate:")
    generate_report(conf_data)
    generate_cfg_h(conf_data)
    generate_cfg_c(conf_data)
 
    

