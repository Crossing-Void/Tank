
struct bits {
	unsigned char hit : 1;
	unsigned char speedUp : 1;
	unsigned char sp_disable : 1;
	unsigned char mp_disable : 1;
	unsigned char freeze : 1;
	unsigned char sp_up : 1;
	unsigned char mp_up : 1;
	unsigned char hp_up : 1;
};

struct position {
	double pointX;
	double pointY;
	double angle;

};

struct speedInformation {
	double speed;
	double angleInterval;
};

struct values {
	double hp;
	double sp;
	double mp;
};
union byte_bit 
{
	bits b; 
	unsigned char B;
};
struct userData {
	char name[20];
	struct position pos;
	struct speedInformation speed;
	struct values value;
	int t;
	union byte_bit status;

};



struct vxy {
	double vx;
	double vy;
};

struct enemyProfile
{
	char name[20];
	struct position pos;
	struct vxy V;
	struct values value;
	union byte_bit status;
	double width = 20;
	bool enable = 1;
};

struct weaponProfile
{
	char name[20];
	struct position pos;
	struct values value;
	double Velocity;
	struct vxy V;
	double range;
	int counter;
	double diameter = 10;
	bool enable = 0;
};

struct itemProfile
{
	char c;
	struct position pos;
	int counter;
	float diameter = 15;
	bool enable = 0;
};
