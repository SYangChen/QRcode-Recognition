#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#define _B_ 0
#define _F_ 1
#define _A_ 2
#define _G_ 3
#define _C_ 4
#define _D_ 5
#define _E_ 6
#define _._ 7

using namespace std ;

int initial_test( void ) ;
int pin_off( void ) ;
int end_reset( void ) ;
int choose_digits( int req ) ;

int main() {
	initial_test() ;
	int a ;
	while( cin >> a )
		choose_digits( a ) ;
	end_reset() ;
}

int initial_test(void){
	//將8個pin角 都export 產生能操作的node
	//if any one fail return -1;

	//將8個pin角 的node direction都改成 output
	//if any one fail return -1;

	//將8個pin角 的node output值 都改成 1
	//if any one fail return -1;

	//將8個pin角 的node output值 再改回 0
	//if any one fail return -1;
	int valuefd, exportfd, directionfd;
    printf("GPIO initializing...\n");
    // The GPIO has to be exported to be able to see it in sysfs
	
	string pin[8] = { "919", "916", "917", "918", "906", "915", "920", "921" } ;
	string temp ;
	for ( int i = 0 ; i < 8 ; ++i ) {
		exportfd = open("/sys/class/gpio/export", O_WRONLY);
		if (exportfd < 0)
		{
			cout << "Cannot open GPIO to export it("+pin[i]+")\n";
			return -1 ; // exit(1);
		}
	  
		write(exportfd, pin[i].c_str(), 4);
		close(exportfd);
		cout << "GPIO exported successfully : " << pin[i] << endl ;
		// Update the direction of the GPIO to be an output
		
		// -----------------------
		
		temp = "/sys/class/gpio/gpio"+pin[i]+"/direction";
		directionfd = open(temp.c_str(), O_RDWR);
		if (directionfd < 0)
		{
			cout << "Cannot open GPIO direction it("+pin[i]+")\n" ;
			return -1 ; // exit(1);
		}
	  
		write(directionfd, "out", 4);
		close(directionfd);
		cout << "GPIO direction set as output successfully : " << pin[i] << endl ;
		// Get the GPIO value ready to be toggled
	}
		// -----------------------
	for ( int i = 0 ; i < 8 ; ++i ) {
		// pin on
		temp = "/sys/class/gpio/gpio"+pin[i]+"/value";
		valuefd = open(temp.c_str(), O_RDWR);
		if (valuefd < 0)
		{
			cout << "Cannot open GPIO value("+pin[i]+")\n" ;
			return -1 ; // exit(1);
		}
		printf("GPIO value opened, now toggling...\n");
		// toggle the GPIO as fast a possible forever, a control c is needed to stop it
		write( valuefd, "1", 2 ) ;
	}
	
	for ( int i = 0 ; i < 8 ; ++i ) {
		// pin off
		temp = "/sys/class/gpio/gpio"+pin[i]+"/value";
		valuefd = open(temp.c_str(), O_RDWR);
		if (valuefd < 0)
		{
			cout << "Cannot open GPIO value("+pin[i]+")\n" ;
			return -1 ; // exit(1);
		}
		printf("GPIO value opened, now toggling...\n");
		// toggle the GPIO as fast a possible forever, a control c is needed to stop it
		write( valuefd, "0", 2 ) ;
	}

	//到這裡都成功
	return 0;
}

int pin_off( void ) {
	
	int valuefd, exportfd, directionfd;
	
	string pin[8] = { "919", "916", "917", "918", "906", "915", "920", "921" } ;
	string temp ;

	for ( int i = 0 ; i < 8 ; ++i ) {
		// pin off
		temp = "/sys/class/gpio/gpio"+pin[i]+"/value";
		valuefd = open(temp.c_str(), O_RDWR);
		if (valuefd < 0)
		{
			cout << "Cannot open GPIO value("+pin[i]+")\n" ;
			return -1 ; // exit(1);
		}
		printf("GPIO value opened, now toggling...\n");
		// toggle the GPIO as fast a possible forever, a control c is needed to stop it
		write( valuefd, "0", 2 ) ;

	}

	return 0;
}

int end_reset(void){

	//將8個pin角 的node output值 都改成 0
	//if any one fail return -1;
	
	//將8個pin角 的node direction都改回 input
	//if any one fail return -1;

	int valuefd, exportfd, directionfd;
    printf("GPIO end...\n");
	
	string pin[8] = { "919", "916", "917", "918", "906", "915", "920", "921" } ;
	string temp ;

	for ( int i = 0 ; i < 8 ; ++i ) {
		// pin off
		temp = "/sys/class/gpio/gpio"+pin[i]+"/value";
		valuefd = open(temp.c_str(), O_RDWR);
		if (valuefd < 0)
		{
			cout << "Cannot open GPIO value("+pin[i]+")\n" ;
			return -1 ; // exit(1);
		}
		printf("GPIO value opened, now toggling...\n");
		// toggle the GPIO as fast a possible forever, a control c is needed to stop it
		write( valuefd, "0", 2 ) ;
		
		// -----------------------------------
		
		temp = "/sys/class/gpio/gpio"+pin[i]+"/direction";
		directionfd = open(temp.c_str(), O_RDWR);
		if (directionfd < 0)
		{
			cout << "Cannot open GPIO direction it("+pin[i]+")\n" ;
			return -1 ; // exit(1);
		}
	  
		write(directionfd, "in", 4);
		close(directionfd);
		cout << "GPIO direction set as input successfully : " << pin[i] << endl ;
	}

	//到這裡都成功
	return 0;
}

int choose_digits(int req){
	
	//根據輸入數字值 0 ~ 9
	//將8個pin角 的node output值
	//改成 對應的7段顯示器輸出
	//if any one fail return -1;

	//如果一開始輸入的值是 -1，
	//表示我們讀到一個 看不懂的 QR-code
	//將8個pin角 的node output值 都改成 0 (也就是全暗)
	//if any one fail return -1;

	bool on[8] ;
	switch ( req ) {
		case 1 :
			on[_B_] = true ;
			on[_F_] = false ;
			on[_A_] = false ;
			on[_G_] = false ;
			on[_C_] = true ;
			on[_D_] = false ;
			on[_E_] = false ;
			on[_._] = false ;
			break ;
		case 2 :
			on[_B_] = true ;
			on[_F_] = false ;
			on[_A_] = true ;
			on[_G_] = true ;
			on[_C_] = false ;
			on[_D_] = true ;
			on[_E_] = true ;
			on[_._] = false ;
			break ;
		case 3 :
			on[_B_] = true ;
			on[_F_] = false ;
			on[_A_] = true ;
			on[_G_] = true ;
			on[_C_] = true ;
			on[_D_] = true ;
			on[_E_] = false ;
			on[_._] = false ;
			break ;
		case 4 :
			on[_B_] = true ;
			on[_F_] = true ;
			on[_A_] = false ;
			on[_G_] = true ;
			on[_C_] = true ;
			on[_D_] = false ;
			on[_E_] = false ;
			on[_._] = false ;
			break ;
		case 5 :
			on[_B_] = false ;
			on[_F_] = true ;
			on[_A_] = true ;
			on[_G_] = true ;
			on[_C_] = true ;
			on[_D_] = true ;
			on[_E_] = false ;
			on[_._] = false ;
			break ;
		case 6 :
			on[_B_] = false ;
			on[_F_] = true ;
			on[_A_] = true ;
			on[_G_] = true ;
			on[_C_] = true ;
			on[_D_] = true ;
			on[_E_] = true ;
			on[_._] = false ;
			break ;
		case 7 :
			on[_B_] = true ;
			on[_F_] = false ;
			on[_A_] = true ;
			on[_G_] = false ;
			on[_C_] = true ;
			on[_D_] = false ;
			on[_E_] = false ;
			on[_._] = false ;
			break ;
		case 8 :
			on[_B_] = true ;
			on[_F_] = true ;
			on[_A_] = true ;
			on[_G_] = true ;
			on[_C_] = true ;
			on[_D_] = true ;
			on[_E_] = true ;
			on[_._] = false ;
			break ;
		case 9 :
			on[_B_] = true ;
			on[_F_] = true ;
			on[_A_] = true ;
			on[_G_] = true ;
			on[_C_] = true ;
			on[_D_] = false ;
			on[_E_] = false ;
			on[_._] = false ;
			break ;
		case 0 :
			on[_B_] = true ;
			on[_F_] = true ;
			on[_A_] = true ;
			on[_G_] = false ;
			on[_C_] = true ;
			on[_D_] = true ;
			on[_E_] = true ;
			on[_._] = false ;
			break ;
		default :
			on[_B_] = false ;
			on[_F_] = false ;
			on[_A_] = false ;
			on[_G_] = false ;
			on[_C_] = false ;
			on[_D_] = false ;
			on[_E_] = false ;
			on[_._] = false ;
			break ;
	}

	int valuefd, exportfd, directionfd;
	
	string pin[8] = { "919", "916", "917", "918", "906", "915", "920", "921" } ;
	string temp ;

	for ( int i = 0 ; i < 8 ; ++i ) {
		// pin on
		temp = "/sys/class/gpio/gpio"+pin[i]+"/value";
		valuefd = open(temp.c_str(), O_RDWR);
		if (valuefd < 0)
		{
			cout << "Cannot open GPIO value("+pin[i]+")\n" ;
			return -1 ; // exit(1);
		}
		// printf("GPIO value opened, now toggling...\n");
		// toggle the GPIO as fast a possible forever, a control c is needed to stop it
		write( valuefd, ( on[i] ? "1" : "0" ), 2 ) ;
		
	}

	//到這裡都成功
	return 0;
}