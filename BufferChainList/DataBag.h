#if !define DATABAG
#define DATABAG
#define DataBagMaxLen  32768 //32KB

class DataBag
{
	public:

	DataBag(int id, unsigned int offset ,char* data);
	int get_id();
	unsigned int get_offset();
	char* get_data();

	private:

	int p_id;
	unsigned int p_offset;
	char p_data[DataBagMaxLen];
};

#endif