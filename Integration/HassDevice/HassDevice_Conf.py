
from io import StringIO
import sys
import json
import os 
sys.path.insert(0, '/Users/tranxuan/Nextcloud/HDD/xuantran/Workspace/02_SW/MeshDevice/Integration/CodeGen')
from CodGenLib import cdlib_get_value, cdlib_push

dir_path = os.path.dirname(os.path.realpath(__file__))

def hassdevice_forward(conf_data):
    print("- HassDevice_forward:")
    return conf_data

def generate_report(conf_data):
    report_content = ""
    report_content += "General:\r\n"
    report_content += "     Id  : " + str(cdlib_get_value(conf_data['HassDevice']['General']['Id'],1,1)) +"\r\n"
    report_content += "     Name: " + str(cdlib_get_value(conf_data['HassDevice']['General']['Name'],1,1)) 
    report_file = open(os.path.join(dir_path,"HassDevice_Report.txt"), "w")
    report_file.write(report_content)
    report_file.close()

def generate_cfg_h(conf_data):
    cfg_ht_file = open(dir_path+"/HassDevice_Cfg.ht","r")
    cfg_h_file_content = cfg_ht_file.read()
    cfg_h_setting = ""
    cfg_h_setting += "#define DEVICE_NAME        \"" + str(cdlib_get_value(conf_data['HassDevice']['General']['Name'],1,1)) +"\"\r\n"
    cfg_h_setting += "#define DEVICE_ID          \"" + str(cdlib_get_value(conf_data['HassDevice']['General']['Id'],1,1)) +"\"\r\n"
    cfg_h_setting += "#define HASS_DEVICE_AVAILABILITY_TOPIC  \"" + str(cdlib_get_value(conf_data['HassDevice']['General']['Name'],1,1)) +"/avai"+"\"\r\n"
    cfg_h_file_content = cfg_h_file_content.replace("<CONFIGURATION SETTING>", cfg_h_setting)
    cfg_ht_file.close()
    # generate the files
    cfg_h_file = open(os.path.join(dir_path,"HassDevice_Cfg.h"), "w")
    cfg_h_file.write(cfg_h_file_content)
    cfg_h_file.close()
def generate_cfg_c(conf_data):
    return


def hassdevice_generate(conf_data):
    print("- HassDevice_generate:")
    generate_report(conf_data)
    generate_cfg_h(conf_data)
    generate_cfg_c(conf_data)
 
    

