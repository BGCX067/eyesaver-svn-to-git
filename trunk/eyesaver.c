/*
 
This program helps reducing the levels of eye strain experienced from prolonged computer use.

Copyright (C) <2012>  Shubhrajyoti Mohapatra <sjmohapatra1@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, if not, write to the
Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
or see <http://www.gnu.org/licenses/>.

The function idle_time uses the source code from xprintidle by
Eivind Magnus Hvidevold <hvidevold@gmail.com>. xprintidle is licensed under
the GNU GPL, version 2 _only_.

*/


#include <gtk/gtk.h>
#include <stdlib.h>
#include "X11/Xlib.h"
#include "X11/extensions/dpms.h"
#include "X11/extensions/scrnsaver.h"
#define COMMAND_LEN 20
#define DATA_SIZE 512


void help_window();
static void hello( GtkWidget *widget,
                   gpointer   data )
{
    	g_print ("Stop staring at me\n");
}

static 
gboolean delete_event( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{
  
	gtk_main_quit();
    	//g_print ("delete event occurred\n");
   	return FALSE;
}
static 
gboolean delete_event1( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{
  
	gtk_main_quit();
    //	g_print ("delete event occurred\n");
   	return FALSE;
}

static void 
destroy( GtkWidget *widget,
                     gpointer   data )
{
    	gtk_main_quit ();
	
}

	
static gboolean
button_press_callback (GtkWidget      *event_box,
                       GdkEventButton *event,
                       gpointer        data)
{
  	
	//g_print ("\n Let's us call help_window()");
	(void)help_window();
  	
  	return FALSE;
}

void 
help_window()
{
	GtkWidget *window1;
    	GtkWidget *button;
    	GtkWidget *table;
    	GtkWidget *notebook;
   	GtkWidget *frame;
    	GtkWidget *label_t1;
    	GtkWidget *frame1;
    	GtkWidget *label1;
	GtkWidget *label;
    	GtkWidget *checkbutton;

	GtkTextBuffer *buffer1;

    	char eye[32]="EyeSaver";
   	char about[32]="About us";
	char *buffer_eye;
	char *buffer_about;
	char ch;
    	int i=0;
	FILE *fp1, *fp2;
	fp1=fopen("eye_health","r");
	if(fp1==NULL)
	{
		printf("\nhello\n");
		return;
	}
	while((ch=fgetc(fp1))!=EOF)
	{
		i++;
	}
	fclose(fp1);
	//printf("\n 1. i=%d\n",i);
	buffer_eye=malloc((sizeof(char)) * i);
	i=0;
	fp1=fopen("eye_health","r");
	while((ch=fgetc(fp1))!=EOF)
	{
		*(buffer_eye+i++)=ch;
	}
	fclose(fp1);
	
	i=0;
	fp2=fopen("about_us","r");
	if(fp2==NULL)
		return;
	while((ch=fgetc(fp2))!=EOF)
	{
		i++;
	}
	fclose(fp2);
	//printf("\n 2. i=%d\n",i);
	buffer_about=malloc(sizeof(char) * i);
	i=0;
	fp2=fopen("about_us","r");
	while((ch=fgetc(fp2))!=EOF)
	{
		//*(buffer_about+i++)=ch;
		buffer_about[i++]=ch;
	}
	fclose(fp2);
	//printf("\n%s",buffer_about);
        
    	window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    	gtk_window_set_position(GTK_WINDOW(window1), GTK_WIN_POS_CENTER);
    	
    
    	gtk_container_set_border_width (GTK_CONTAINER (window1), 10);
	gtk_window_maximize (GTK_WINDOW(window1));
    	table = gtk_table_new (2, 1, FALSE);
    	gtk_container_add (GTK_CONTAINER (window1), table);
    
   
    	notebook = gtk_notebook_new ();
    	gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook), GTK_POS_TOP);
    	gtk_table_attach_defaults (GTK_TABLE (table), notebook, 0, 1, 0, 1);
    	gtk_widget_show (notebook);
    
	
	frame = gtk_frame_new (NULL);
	gtk_container_set_border_width (GTK_CONTAINER (frame), 10);
	gtk_widget_set_size_request (frame, 100, 75);
	gtk_widget_show (frame);
	
	//label = gtk_label_new (buffer_eye);
	label_t1 = gtk_text_view_new();
	buffer1 = gtk_text_view_get_buffer (GTK_TEXT_VIEW (label_t1));
	gtk_text_buffer_set_text (buffer1,buffer_eye, -1);
	
	GtkWidget *scroll;
	scroll = gtk_scrolled_window_new(NULL,NULL);
	gtk_container_add (GTK_CONTAINER (scroll), label_t1);
	gtk_container_add (GTK_CONTAINER (frame), scroll);
	gtk_text_view_set_editable (GTK_TEXT_VIEW (label_t1),FALSE);
	gtk_widget_show (label_t1);
	gtk_widget_show(scroll);
	label = gtk_label_new (eye);
	gtk_notebook_append_page (GTK_NOTEBOOK (notebook), frame, label);




	frame1 = gtk_frame_new (NULL);
	gtk_container_set_border_width (GTK_CONTAINER (frame1), 10);
	gtk_widget_set_size_request (frame, 100, 75);
	gtk_widget_show (frame1);
	
	label1 = gtk_label_new (buffer_about);
	gtk_container_add (GTK_CONTAINER (frame1), label1);
	gtk_widget_show (label1);
	
	label1 = gtk_label_new (about);
	gtk_notebook_append_page (GTK_NOTEBOOK (notebook), frame1, label1);


	button = gtk_button_new_with_label ("close");
	gtk_button_set_relief(GTK_BUTTON(button),GTK_RELIEF_NORMAL);
	gtk_widget_set_size_request(GTK_WIDGET(button),100,35);
    	//g_signal_connect (button, "clicked",
	//			  G_CALLBACK (destroy1), window1);
    
    	g_signal_connect_swapped (button, "clicked",
		      G_CALLBACK (delete_event1), NULL);
	g_signal_connect (window1, "destroy",
		      G_CALLBACK (destroy), NULL);
	g_signal_connect (window1, "delete-event",
	              G_CALLBACK (delete_event1), NULL);
	
	
    	gtk_table_attach(GTK_TABLE (table), button, 0, 1, 1, 2,GTK_SHRINK,GTK_SHRINK,0,0);
    	//gtk_widget_show (button);
      
        
    	gtk_widget_show (table);
    	gtk_widget_show (window1);
    	free(buffer_eye);
	free(buffer_about);
    	gtk_main ();
}
void 
show(int argc, char *argv[])
{
	   
	GtkWidget *window;
	GtkWidget *button_ok;
	GtkWidget *label_warn;
	GtkWidget *label_info;  
	GtkWidget *label_hbox11;
	GtkWidget *label_hbox12;
	GtkWidget *label_message1;  
	GtkWidget *label_seconds;
	GtkWidget *label_message2;
	GtkWidget *label_developer;
	GtkWidget *button_email;
	GtkWidget *button_web;
	GtkWidget *label_free;	
	GtkWidget *table;
	GtkWidget *h_box1;
	GtkWidget *v_box1;
	GtkWidget *h_box2;
	GtkWidget *frame1;
	GtkWidget *frame2;
	GtkWidget *image;
	GtkWidget *event_box;		
	char *warn={"STOP STARING!!"};
	char *info={"Staring at screen for long, causes severe strain to your eyes.Relax for a while by looking around for 20 seconds now."};
	char *hbox11={"Click on the eye"};
	char *hbox12={"to know more!"};
	char *message1={"I will disappear automatically in 30 secs, if you allow your eyes to relax now."};
	char *seconds={"20 seconds"};
	char *message2={"Please allow your eyes to relax"};
	char *developer={"Developed by:"};
	char *name={"Shubhrajyoti"};
	char *free={"Free Software"};
	char *link_email={"mailto:sjmohapatra1@gmail.com"};
	char *link_web={"http://code.google.com/p/eyesaver"};
	

	gtk_init (&argc, &argv);
   
      	/**************WINDOW*********************/
    	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
   
    	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	
	//gtk_window_set_resizable(GTK_WINDOW(window), TRUE);  
 
    	g_signal_connect (window, "delete_event",
		      G_CALLBACK (delete_event), NULL);
    
 
    	g_signal_connect (window, "destroy",
		      G_CALLBACK (destroy), NULL);
    
    	
    	gtk_container_set_border_width (GTK_CONTAINER( window), 20);
	//gtk_window_unmaximize(GTK_WINDOW(window)); 
	//gtk_window_unfullscreen(GTK_WINDOW(window)); 
	//gtk_window_set_decorated(GTK_WINDOW(window),TRUE);
	//gtk_window_set_type_hint(GTK_WINDOW(window),GDK_WINDOW_TYPE_HINT_DIALOG);

	//gtk_window_set_icon_from_file(GTK_WINDOW(window),"eye.png",NULL);
	gtk_window_set_opacity( GTK_WINDOW(window), 0.8); 
	gtk_window_set_deletable(GTK_WINDOW(window), TRUE);

	(void)gtk_window_set_default_icon_from_file("eye.png", NULL);


	/**************MAIN TABLE*********************/
	
	table = gtk_table_new ( 6, 1, FALSE );
	gtk_container_add (GTK_CONTAINER (window), table);
	
	/**************first row*********************/
	/*char *markup;
	
  	markup = g_markup_printf_escaped ("<span><big><b>%s</b></big></span>", warn);
	label_warn = gtk_label_new(warn);
	gtk_label_set_markup (GTK_LABEL (label_warn), markup);
	g_free (markup);*/
	GtkTextBuffer *buffer;
	PangoFontDescription *font_desc;
	static GdkColor colorred, color_bg;

	label_warn = gtk_text_view_new ();
	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (label_warn));
	gtk_text_buffer_set_text (buffer,warn, -1);

	font_desc = pango_font_description_from_string ("Serif 15");
	pango_font_description_set_weight   (font_desc,PANGO_WEIGHT_ULTRABOLD);
                                                         
	gtk_widget_modify_font (label_warn, font_desc);
	pango_font_description_free (font_desc);
	
	gdk_color_parse ("red", &colorred);
	gdk_color_parse ("#F2F1F0", &color_bg);
	gtk_widget_modify_text (label_warn, GTK_STATE_NORMAL, &colorred);
        gtk_widget_modify_base(label_warn, GTK_STATE_NORMAL, &color_bg);
	
  	//gdk_color_parse ("#0080FF", &colorred);
  	//gtk_widget_modify_fg (label_info, GTK_STATE_NORMAL, color);
	//gtk_widget_modify_text(label_info, GTK_STATE_NORMAL, &colorred);
	gtk_text_view_set_editable (GTK_TEXT_VIEW (label_warn),FALSE);
	gtk_widget_show(label_warn);
	gtk_table_attach(GTK_TABLE(table), label_warn, 0, 1, 0, 1,GTK_SHRINK,GTK_SHRINK,0,0);
	

	/**************second row*********************/

	GtkTextBuffer *buffer1;
	PangoFontDescription *font_desc1;
	static GdkColor colorgreen, colorblack;	

	frame1 = gtk_frame_new (NULL);
	//gtk_frame_set_label (GTK_FRAME (frame1), info);
	gtk_widget_set_size_request(GTK_WIDGET(frame1),400,50);
	label_info = gtk_text_view_new ();

	buffer1 = gtk_text_view_get_buffer (GTK_TEXT_VIEW (label_info));
	gtk_text_buffer_set_text (buffer1,info, -1);

	font_desc1 = pango_font_description_from_string ("Monospace 9");
	
                                                         
	
	
	
	gdk_color_parse ("green", &colorgreen);
	gdk_color_parse ("black", &colorblack);
	gtk_widget_modify_text (label_info, GTK_STATE_NORMAL, &colorgreen);
	
	pango_font_description_set_style(font_desc1,PANGO_STYLE_ITALIC);
	gtk_widget_modify_font (label_info, font_desc1);
		
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW (label_info),GTK_WRAP_WORD);
	gtk_text_view_set_justification(GTK_TEXT_VIEW (label_info), GTK_JUSTIFY_CENTER);

	pango_font_description_free (font_desc1);
	//gtk_label_set_line_wrap(GTK_LABEL(label_info),TRUE);
	//gtk_label_set_justify(GTK_LABEL(label_info), GTK_JUSTIFY_FILL);
        gtk_widget_modify_base(label_info, GTK_STATE_NORMAL, &colorblack);
        gtk_text_view_set_editable (GTK_TEXT_VIEW (label_info),FALSE);                          
	gtk_widget_show(label_info);
	gtk_frame_set_shadow_type (GTK_FRAME(frame1), GTK_SHADOW_OUT);
	gtk_container_add (GTK_CONTAINER (frame1), label_info);
	gtk_table_attach(GTK_TABLE(table), frame1, 0, 1, 1, 2,GTK_SHRINK,GTK_SHRINK,0,10);
	gtk_widget_show(frame1);
  	//gtk_container_add (GTK_CONTAINER (window), frame1);
	
	/**************Third Row*********************/
	
	h_box1 = gtk_hbox_new (FALSE,0);
	label_hbox11=gtk_label_new(hbox11);
	gtk_widget_show(label_hbox11);
	gtk_box_pack_start (GTK_BOX (h_box1), label_hbox11, FALSE, FALSE, 0);

	image = gtk_image_new_from_file ("eye.png");
	gtk_widget_show(image);

	event_box = gtk_event_box_new ();
	gtk_container_add (GTK_CONTAINER (event_box), image);
	g_signal_connect (G_OBJECT (event_box),"button_press_event",
                    		G_CALLBACK (button_press_callback),image);
	
	gtk_box_pack_start (GTK_BOX (h_box1), event_box, FALSE, FALSE, 0);
	gtk_widget_show(event_box);

	
	label_hbox12=gtk_label_new(hbox12);
	gtk_widget_show(label_hbox12);
	gtk_box_pack_start (GTK_BOX (h_box1), label_hbox12, FALSE, FALSE, 0);
	
	gtk_table_attach(GTK_TABLE(table), h_box1, 0, 1, 2, 3,GTK_SHRINK,GTK_SHRINK,0,10);
	gtk_widget_show(h_box1);

         /**************Fourth Row*********************/
	
	GtkTextBuffer *buffer2;
	PangoFontDescription *font_desc2;
	static GdkColor colorblue;	
		
	frame2 = gtk_frame_new (NULL);
	gtk_widget_set_size_request(GTK_WIDGET(frame2),400,50);	
	gtk_frame_set_shadow_type (GTK_FRAME(frame2), GTK_SHADOW_OUT);	
	
	v_box1=gtk_vbox_new(TRUE,0);
	
	label_message1 = gtk_text_view_new ();

	buffer2 = gtk_text_view_get_buffer (GTK_TEXT_VIEW (label_message1));
	gtk_text_buffer_set_text (buffer2,message1, -1);

	font_desc2 = pango_font_description_from_string ("Monospace 9");                                                    	
	
	gdk_color_parse ("blue", &colorblue);
	gtk_widget_modify_text (label_message1, GTK_STATE_NORMAL, &colorblue);
	gtk_widget_modify_base (label_message1, GTK_STATE_NORMAL, &color_bg);
	//pango_font_description_set_style(font_desc1,PANGO_STYLE_ITALIC);
	gtk_widget_modify_font (label_message1, font_desc2);
		
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW (label_message1),GTK_WRAP_WORD);
	gtk_text_view_set_justification(GTK_TEXT_VIEW (label_message1), GTK_JUSTIFY_CENTER);

	pango_font_description_free (font_desc2);
	gtk_text_view_set_editable (GTK_TEXT_VIEW (label_message1),FALSE);
	
	gtk_box_pack_start (GTK_BOX (v_box1), label_message1, FALSE, FALSE, 0);

	gtk_widget_show(label_message1);
	/*label_seconds=gtk_label_new(seconds);
	gtk_label_set_justify(GTK_LABEL(label_seconds), GTK_JUSTIFY_CENTER);
        gtk_widget_show(label_seconds);
	gtk_box_pack_start (GTK_BOX (v_box1), label_seconds, FALSE, FALSE, 0);
	
	label_message2=gtk_label_new(message2);
	char *markup3;
	markup3 = g_markup_printf_escaped ("<span><i> %s</i></span>", message2);
	gtk_label_set_markup (GTK_LABEL (label_message2), markup3);
	g_free (markup3);
	gtk_label_set_justify(GTK_LABEL(label_message2), GTK_JUSTIFY_FILL);
        gtk_widget_show(label_message2);
	gtk_box_pack_start (GTK_BOX (v_box1), label_message2, FALSE, FALSE, 0);*/
	gtk_widget_show(v_box1);

	gtk_container_add (GTK_CONTAINER (frame2), v_box1);
	gtk_table_attach(GTK_TABLE(table), frame2, 0, 1, 3, 4,GTK_SHRINK,GTK_SHRINK,0,5);
	gtk_widget_show(frame2);
  	//gtk_container_add (GTK_CONTAINER (window), frame);

	/**************Counter Row********************* 
	GtkWidget *label_counter;
	char sec[2];
	int second;
	second=g_timeout_add_full( G_PRIORITY_HIGH, 1000, counter, &second, NULL);
	sprintf( sec, "%d", second );
	label_counter=gtk_label_new(sec);
	gtk_table_attach(GTK_TABLE(table), label_counter, 0, 1, 4, 5,GTK_SHRINK,GTK_SHRINK,0,10);	
	gtk_widget_show(label_counter);*/
	
	 /**************Fifth(button) Row*********************/ 
	
	
	button_ok = gtk_button_new_with_label ("Close Me Now");
			
	gtk_button_set_relief(GTK_BUTTON(button_ok),GTK_RELIEF_NORMAL);
	gtk_widget_set_size_request(GTK_WIDGET(button_ok),120,30);
			
	//g_signal_connect (button_ok, "clicked",
	//			  G_CALLBACK (hello), NULL);
    
    	g_signal_connect_swapped (button_ok, "clicked",
			      G_CALLBACK (gtk_widget_destroy), window);
    
      	
	gtk_table_attach(GTK_TABLE(table), button_ok, 0, 1, 5, 6,GTK_SHRINK,GTK_SHRINK,0,20);
	
        gtk_widget_show(button_ok);		

	/**************Sixth(link) Row*********************/ 

	//GtkTextBuffer *buffer3,*buffer4,*buffer5;
	//PangoFontDescription *font_desc3,*font_desc4;

	h_box2=gtk_hbox_new(FALSE,0);
	label_developer = gtk_label_new(developer);
	char *markup3;
	  
	markup3 = g_markup_printf_escaped ("<span size=\"smaller\">%s</span>", developer);
	gtk_label_set_markup (GTK_LABEL (label_developer), markup3);
	g_free (markup3);
	//buffer3 = gtk_text_view_get_buffer (GTK_TEXT_VIEW (label_developer));
	//gtk_text_buffer_set_text (buffer2,developer, -1);
	//font_desc3 = pango_font_description_from_string ("Monospace 8");                                                    	
	
	//gdk_color_parse ("blue", &colorblue);
	//gtk_widget_modify_text (label_developer, GTK_STATE_NORMAL, &colorblue);
	
	//pango_font_description_set_style(font_desc1,PANGO_STYLE_ITALIC);
	//gtk_widget_modify_font (label_developer, font_desc3);
		
	//gtk_text_view_set_justification(GTK_TEXT_VIEW (label_developer), GTK_JUSTIFY_LEFT);

	//pango_font_description_free (font_desc3);

	//gtk_box_pack_start (GTK_BOX (h_box2), label_developer, FALSE, FALSE, 0);
	//gtk_widget_show(label_developer);
	
	button_email=gtk_link_button_new_with_label(link_email, name);
	
	//gtk_widget_set_size_request(GTK_WIDGET(button_email),100,5);
	gtk_box_pack_start (GTK_BOX (h_box2), button_email, FALSE, FALSE, 0);
	gtk_widget_show(button_email);

	button_web=gtk_link_button_new_with_label(link_web, free);
		
	gtk_box_pack_start (GTK_BOX (h_box2), button_web, FALSE, FALSE, 0);
	gtk_widget_show(button_web);
	gtk_box_set_spacing(GTK_BOX (h_box2), 200);
	//gtk_button_box_set_layout(GTK_BOX (h_box2), GTK_BUTTONBOX_EDGE);
	gtk_table_attach(GTK_TABLE(table), h_box2, 0, 1, 6, 7,GTK_SHRINK,GTK_SHRINK,0,0);				
	gtk_widget_show(h_box2);

	/**************show all and delete automatically*********************/
			   	
    	gtk_widget_show (table);
    	gtk_widget_show (window);
        g_timeout_add (30000, (GSourceFunc)gtk_widget_destroy, window);       	
    	gtk_main ();
	
}

long int 
idle_time()
{
	XScreenSaverInfo ssi;
  	Display *dpy;
  	int event_basep, error_basep;
	unsigned long _idleTime;
  	int dummy;
  	CARD16 standby, suspend, off;
  	CARD16 state;
  	BOOL onoff;

  	
  	dpy = XOpenDisplay(NULL);
  	if (dpy == NULL) {
    		fprintf(stderr, "couldn't open display\n");
    		return 1;
  		}
  
  	if (!XScreenSaverQueryExtension(dpy, &event_basep, &error_basep)) {
    		fprintf(stderr, "screen saver extension not supported\n");
    		return 1;
  		}
  
  	if (!XScreenSaverQueryInfo(dpy, DefaultRootWindow(dpy), &ssi)) {
    		fprintf(stderr, "couldn't query screen saver info\n");
    		return 1;
  		}
  
	if (DPMSQueryExtension(dpy, &dummy, &dummy)) {
    	if (DPMSCapable(dpy)) {
      	DPMSGetTimeouts(dpy, &standby, &suspend, &off);
      	DPMSInfo(dpy, &state, &onoff);

      	if (onoff) {
        	switch (state) {
          		case DPMSModeStandby:
            		/* this check is a littlebit paranoid, but be sure */
            		if (_idleTime < (unsigned) (standby * 1000))
              			ssi.idle += (standby * 1000);
            		break;
          		case DPMSModeSuspend:
            		if (_idleTime < (unsigned) ((suspend + standby) * 1000))
              			ssi.idle += ((suspend + standby) * 1000);
            		break;
          		case DPMSModeOff:
            		if (_idleTime < (unsigned) ((off + suspend + standby) * 1000))
              			ssi.idle += ((off + suspend + standby) * 1000);
            		break;
          		case DPMSModeOn:
          		default:
            		break;
        		}
      		}
    	} 
  	}
 	//printf("%lu\n", ssi.idle);

	
  	XCloseDisplay(dpy);

   	return ssi.idle;
}

int
main(int argc, char *argv[])
{
	long int idletime, idletime1, delay=0;
	int time=0;

 
	while(1)
	{
		time=0;
		delay=0;
		while(time<20)
		{
			time=time+1;
			sleep(60);
			
			
			//printf("\n1-time is %d\n",time);
			idletime=idle_time();
			//printf("\n1-idle time is %ld\n",idletime);
			if(idletime>=240000)
				delay=idletime;
			//printf("\n2-idle time is(delay) %ld\n",delay);
			if(delay>=480000)
			{
				delay=0;
				time=0;
				//printf("\n1-Timer Reset!!!\n");
			}
			if(time>=18 && time <20)
			{
				//printf("\n2-time is %d\n",time);
				idletime=idle_time();
				//printf("\n3-idle time is %ld\n",idletime);
				if(idletime>=60000)
				{
					//printf("\n4-idletime is %ld\n",idletime);
					sleep(60);
					time=time+1;
					idletime=idle_time();
					//printf("\n5-idletime is %ld\n",idletime);
					if(idletime>=110000)
					{
						time=0;
						//printf("\n2-Timer Reset!!!\n");
					}	
					//printf("\ngoing out of innnerloop\n");
				}
				//printf("\nGoing out of outer loop\n");
				
			}
			
			if(time==20)
			{
				//printf("\n3-time(19th loop) is %d\n",time);
				idletime1=idle_time();
				//printf("\n6-idletime1 is %ld\n",idletime1);
				sleep(10);
				idletime=idle_time();
				//printf("\n7-idletime is %ld\n",idletime);
				if(idletime>=idletime1+9000)
					sleep(10);
				idletime1=idle_time();
				//printf("\n8-idletime1 is %ld\n",idletime1);
				if(idletime1>=idletime+9000)
				{
					sleep(40);
					idletime=idle_time();
					//printf("\n9-idletime is %ld\n",idletime);
					if(idletime>=idletime1+40000)
					{
						time=0;
						//printf("\n3-Timer reset!!!");
					}
				}
			}
			//printf("\nexiting while\n");
		}
		//printf("\ntime to pop up\n");
		show(argc,argv);
				
	}
		
       	return 0;
}
