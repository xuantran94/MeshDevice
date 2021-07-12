
from io import StringIO
import sys
import json
import os 
sys.path.insert(0, '/Users/tranxuan/Nextcloud/HDD/xuantran/Workspace/02_SW/MeshDevice/Integration/CodeGen')
from CodGenLib import cdlib_get_value, cdlib_push

dir_path = os.path.dirname(os.path.realpath(__file__))

def hass_forward(conf_data):
    print("- Hass_forward:")
    return conf_data

def generate_report(conf_data):
    report_content = ""
    report_content += "General:\r\n"
    report_content += "     Topic: " + cdlib_get_value(conf_data['Hass']['General']['Topic'],1,1) 
    report_file = open(os.path.join(dir_path,"Hass_Report.txt"), "w")
    report_file.write(report_content)
    report_file.close()

def generate_cfg_h(conf_data):
    cfg_ht_file = open(dir_path+"/Hass_Cfg.ht","r")
    cfg_h_file_content = cfg_ht_file.read()
    cfg_h_setting = ""
    cfg_h_setting += "#define HASS_TOPIC        \"" + cdlib_get_value(conf_data['Hass']['General']['Topic'],1,1) +"\"\r\n"
    cfg_h_file_content = cfg_h_file_content.replace("<CONFIGURATION SETTING>", cfg_h_setting)
    cfg_ht_file.close()
    # generate the files
    cfg_h_file = open(os.path.join(dir_path,"Hass_Cfg.h"), "w")
    cfg_h_file.write(cfg_h_file_content)
    cfg_h_file.close()
def generate_cfg_c(conf_data):
    return


def hass_generate(conf_data):
    print("- hass_generate:")
    generate_report(conf_data)
    generate_cfg_h(conf_data)
    generate_cfg_c(conf_data)
 
    

