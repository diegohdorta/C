

# Calibrating Touchscreen

Add the following lines inside the `/etc/profile` file:

```console
	export QT_DEBUG_PLUGINS=1
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib/arm-linux-gnueabihf/
	export QT_PLUGIN_PATH=/usr/lib/plugins
	export QT_QPA_FONTDIR=/usr/lib/fonts
	export QT_QPA_PLATFORM_PLUGIN_PATH=/usr/lib/plugins/platforms
	export QT_QPA_PLATFORM=linuxfb
	export QT_QPA_GENERIC_PLUGINS=tslib:/dev/input/event[insert event number of your touchscreen here]
	export QT_QPA_EVDEV_TOUCHSCREEN_PARAMETERS=/dev/input/event[insert event number of your touchscreen here]
	export TSLIB_TSEVENTTYPE='INPUT'
	export TSLIB_CALIBFILE='/etc/pointercal'
	export TSLIB_CONFFILE='/etc/ts.conf'
	export TSLIB_CONSOLEDEVICE='none'
	export TSLIB_FBDEVICE='/dev/fb0'
	export TSLIB_PLUGINDIR='/usr/lib/ts'
	export TSLIB_TSDEVICE='/dev/input/event[insert event number of your touchscreen here]'
```

Run your application with the line: 

```console
	# ./app_example -platform linuxfb -plugin \
	evdevtouch:/dev/input/event[insert event number of your touchscreen here]
```
