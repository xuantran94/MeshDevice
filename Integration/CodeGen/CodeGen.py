
# importing sys
import sys
import yaml
from yaml.loader import SafeLoader
import io

sys.path.insert(0, '/Users/tranxuan/Nextcloud/HDD/xuantran/Workspace/02_SW/MeshDevice/Integration/Light')
from Light_Conf import light_forward, light_generate
sys.path.insert(0, '/Users/tranxuan/Nextcloud/HDD/xuantran/Workspace/02_SW/MeshDevice/Integration/HwAbPwm')
from HwAbPwm_Conf import hwabpwm_deviceinfo_forward, hwabpwm_generate
sys.path.insert(0, '/Users/tranxuan/Nextcloud/HDD/xuantran/Workspace/02_SW/MeshDevice/Integration/HwAbDio')
from HwAbDio_Conf import hwabdio_deviceinfo_forward, hwabdio_generate
sys.path.insert(0, '/Users/tranxuan/Nextcloud/HDD/xuantran/Workspace/02_SW/MeshDevice/Integration/Hass')
from Hass_Conf import hass_forward, hass_generate
sys.path.insert(0, '/Users/tranxuan/Nextcloud/HDD/xuantran/Workspace/02_SW/MeshDevice/Integration/HassDevice')
from HassDevice_Conf import hassdevice_forward, hassdevice_generate


# Load the Configuration data 
# Planned: Collect the configuration from the multiple files
with open('Integration/CodeGen/Conf.yaml') as f:
    conf_data = yaml.load(f, Loader=SafeLoader)

print("--------------Code generation is started----------------")
conf_data = hwabpwm_deviceinfo_forward(conf_data)
conf_data = hwabdio_deviceinfo_forward(conf_data)
conf_data = hass_forward(conf_data)
conf_data = hassdevice_forward(conf_data)
conf_data = light_forward(conf_data)

hass_generate(conf_data)
hassdevice_generate(conf_data)
light_generate(conf_data)
hwabpwm_generate(conf_data)
hwabdio_generate(conf_data)
print("--------------Code generation is finished----------------")


# Dump the final configuration data for the validation only
fwdFile = yaml.dump(conf_data)
with io.open('Integration/CodeGen/Conf_Fwd.yaml', 'w', encoding='utf8') as outfile:
    yaml.dump(conf_data, outfile, default_flow_style=False, allow_unicode=True)
