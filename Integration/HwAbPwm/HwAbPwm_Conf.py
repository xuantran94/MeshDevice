
from io import StringIO
import sys
sys.path.insert(0, '/Users/tranxuan/Nextcloud/HDD/xuantran/Workspace/02_SW/MeshDevice/Integration/CodeGen')

from CodGenLib import cdlib_get_value
import os 
dir_path = os.path.dirname(os.path.realpath(__file__))

def hwabpwm_deviceinfo_forward(conf_data):
    print("- hwabpwm_deviceinfo_forward:")
    return conf_data

def generate_report(conf_data):
    report_content = ""
    report_content += "ConfigSet:\r\n"
    if( not conf_data['HwAbPwm']['ConfigSet'] ):
        report_content = "Component is deactivated!\r\n"
    else:
        for signal in conf_data['HwAbPwm']['ConfigSet']:
            report_content += "    Signal: "+signal['Name']+"\r\n"
            report_content += "         ConnectedTo: "+ str(cdlib_get_value(signal['ConnectedTo'],1,1))+"\r\n"
            report_content += "         InitDuty   : "+ str(cdlib_get_value(signal['InitDuty'],1,1))+"\r\n"

    report_file = open(os.path.join(dir_path,"HwAbPwm_Report.txt"), "w")
    report_file.write(report_content)
    report_file.close()

def generate_cfg_h(conf_data):
    cfg_ht_file = open(dir_path+"/HwAbPwm_Cfg.ht","r")
    cfg_h_file_content = cfg_ht_file.read()
    cfg_h_setting = ""
    off_setting = "    STD_OFF\r\n"
    on_setting  = "    STD_ON\r\n"
    cfg_h_setting += "#define HWABPWM_CFG_MODULE_ACTIVE"
    if( not conf_data['HwAbPwm']['ConfigSet'] ):
        print("HwAbPwm component is disbaled")
        cfg_h_setting += off_setting
    else:
        cfg_h_setting += on_setting
        cfg_h_setting += "#define HWABPWM_CFG_DEBUG"
        if(cdlib_get_value(conf_data['HwAbPwm']['General']['DebugEnable'],1,1)):
            cfg_h_setting += on_setting
        else:
            cfg_h_setting += off_setting
        cfg_h_setting += "#define HWABPWM_CFG_INFO"
        if(cdlib_get_value(conf_data['HwAbPwm']['General']['InfoEnable'],1,1)):
            cfg_h_setting += on_setting
        else:
            cfg_h_setting += off_setting

        # number of signal
        cfg_h_setting += "#define HWABPWM_CFG_NUM    " + str(len(conf_data['HwAbPwm']['ConfigSet'])) +'u'

        cfg_h_signals_id =""
        signal_id = 0
        for signal in conf_data['HwAbPwm']['ConfigSet']:
            cfg_h_signals_id += "#define HwAbPwm_"+signal['Name'] + "   " + str(signal_id)+"u\r\n"
            signal_id +=1
        cfg_h_file_content = cfg_h_file_content.replace("<SIGNALS ID>", cfg_h_signals_id)

    cfg_h_file_content = cfg_h_file_content.replace("<CONFIGURATION SETTING>", cfg_h_setting)
    
    cfg_ht_file.close()
    # generate the files
    cfg_h_file = open(os.path.join(dir_path,"HwAbPwm_Cfg.h"), "w")
    cfg_h_file.write(cfg_h_file_content)
    cfg_h_file.close()
def generate_cfg_c(conf_data):
    cfg_ct_file = open(dir_path+"/HwAbPwm_Cfg.ct","r")
    cfg_c_file_content = cfg_ct_file.read()
    cfg_c_signals = ""
    if( not conf_data['HwAbPwm']['ConfigSet'] ):
        return
    else:
        for signal in conf_data['HwAbPwm']['ConfigSet']:
            cfg_c_signals += "  {\r\n"
            cfg_c_signals += "      //" + signal['Name'] + "\r\n"
            cfg_c_signals += "      " + str(cdlib_get_value(signal['ConnectedTo'],1,1)) +",\r\n"
            cfg_c_signals += "      " + str(cdlib_get_value(signal['InitDuty'],1,1)) +",\r\n"
            cfg_c_signals += "  },\r\n"
    cfg_c_file_content = cfg_c_file_content.replace("<SIGNALS CONFIGURATION>", cfg_c_signals)
    cfg_ct_file.close()
    # generate the files
    cfg_c_file = open(os.path.join(dir_path,"HwAbPwm_Cfg.c"), "w")
    cfg_c_file.write(cfg_c_file_content)
    cfg_c_file.close()


def hwabpwm_generate(conf_data):
    print("- hwabpwm_generate:")
    generate_report(conf_data)
    generate_cfg_h(conf_data)
    generate_cfg_c(conf_data)
 
    

