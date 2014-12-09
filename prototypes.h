#define bool unsigned char
#define IIO_MAX_NAME_LENGTH 30

#define FORMAT_SCAN_ELEMENTS_DIR "%s/scan_elements"
#define FORMAT_TYPE_FILE "%s_type"

#define ACCESS_NORM 0
#define ACCESS_DBFS 1

static const char *iio_dir = "/sys/bus/iio/devices/";
static const char *iio_debug_dir = "/sys/kernel/debug/iio/";

/**
 * iioutils_break_up_name() - extract generic name from full channel name
 * @full_name: the full channel name
 * @generic_name: the output generic channel name
 **/
static int iioutils_break_up_name(const char *full_name,
				  char **generic_name);

enum iio_endian {
	IIO_BE,
	IIO_LE,
};

/**
 * struct iio_channel_info - information about a given channel
 * @name: channel name
 * @generic_name: general name for channel type
 * @scale: scale factor to be applied for conversion to si units
 * @offset: offset to be applied for conversion to si units
 * @index: the channel index in the buffer output
 * @bytes: number of bytes occupied in buffer output
 * @mask: a bit mask for the raw output
 * @is_signed: is the raw value stored signed
 * @enabled: is this channel enabled
 **/
struct iio_channel_info {
	char *name;
	char *generic_name;
	float scale;
	float offset;
	unsigned index;
	unsigned bytes;
	unsigned bits_used;
	unsigned shift;
	unsigned int mask;
	unsigned is_signed;
	unsigned enabled;
	enum iio_endian endianness;
	void *extra_field;
};

/**
 * iioutils_get_type() - find and process _type attribute data
 * @is_signed: output whether channel is signed
 * @bytes: output how many bytes the channel storage occupies
 * @mask: output a bit mask for the raw data
 * @device_dir: the iio device directory
 * @name: the channel name
 * @generic_name: the channel type name
 **/
static inline int iioutils_get_type(unsigned *is_signed,
			     unsigned *bytes,
			     unsigned *bits_used,
			     unsigned *shift,
			     unsigned int *mask,
				 enum iio_endian *endianness,
			     const char *device_dir,
			     const char *name,
			     const char *generic_name);

static inline int iioutils_get_param_float(float *output,
				    const char *param_name,
				    const char *device_dir,
				    const char *name,
				    const char *generic_name);

/**
 * bsort_channel_array_by_index() - reorder so that the array is in index order
 *
 **/

static inline void bsort_channel_array_by_index(struct iio_channel_info **ci_array,
					 int cnt);

/**
 * build_channel_array() - function to figure out what channels are present
 * @device_dir: the IIO device directory in sysfs
 * @
 **/
static inline int build_channel_array(const char *device_dir,
			      struct iio_channel_info **ci_array,
			      unsigned int *counter);

static inline void free_channel_array(struct iio_channel_info *ci_array,
			      int num_channels);

/**
 * find_type_by_name() - function to match top level types by name
 * @name: top level type instance name
 * @type: the type of top level instance being sort
 *
 * Typical types this is used for are device and trigger.
 **/
static inline int find_type_by_name(const char *name, const char *type);

/**
 *  find_names() - function to find names installed on the system
 *  @name: null char delimited names
 *  @filter: Allows to filter by device type
 *
 *  Returns the number of devices found
 **/
static inline int find_iio_names(char **names, const char *filter);

static inline int _write_sysfs_int(const char *filename, const char *basedir, int val, int verify, int type, int val2);

static inline int write_sysfs_int(const char *filename, const char *basedir, int val);

static inline int write_sysfs_int_and_verify(const char *filename, const char *basedir, int val);

static inline int write_sysfs_int2(const char *filename, const char *basedir, int val, int val2);

static inline int _write_sysfs_string(const char *filename, const char *basedir, const char *val, int verify);

/**
 * write_sysfs_string_and_verify() - string write, readback and verify
 * @filename: name of file to write to
 * @basedir: the sysfs directory in which the file is to be found
 * @val: the string to write
 **/
static inline int write_sysfs_string_and_verify(const char *filename, const char *basedir,
	const char *val);

static inline int write_sysfs_string(const char *filename, const char *basedir, const char *val);

static inline int read_sysfs_posint(const char *filename, const char *basedir);

static inline int read_sysfs_float(const char *filename, const char *basedir, float *val);

/*
 * Used to quiet warnings
 */
static inline void dummy_funct_quiet(char *ptr);

#define AVAILABLE_TOKEN "_available"
#define SCALE_TOKEN "_scale"

int set_dev_paths(const char *device_name);
int read_sysfs_string(const char *filename, const char *basedir, char **str);
int set_debugfs_paths(const char *device_name);
int read_sysfs_string(const char *filename, const char *basedir, char **str);
int read_reg(unsigned int address);
int write_reg(unsigned int address, unsigned int val);
int write_devattr(const char *attr, const char *str);
int read_devattr(const char *attr, char **str);
int read_devattr_bool(const char *attr, bool *value);
int read_devattr_double(const char *attr, double *value);
int write_devattr_double(const char *attr, double value);
int write_devattr_int(const char *attr, unsigned long long val);
int read_devattr_int(char *attr, int *val);
int read_devattr_slonglong(const char *attr, long long *value);
int write_devattr_slonglong(const char *attr, long long value);
bool iio_devattr_exists(const char *device, const char *attr);
int iio_buffer_open(bool read, int flags);
int find_scan_elements(char *dev, char **elements, unsigned access);
void scan_elements_sort(char **elements);
void scan_elements_insert(char **elements, char *token, char *end);
