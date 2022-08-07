void play_track(int, int, int);
int check_button(void);
int freq_note_map(char);

void setup() {
  Serial.begin(9600);
  DDRD |= B00000100; //set pin 2 as output for speaker, all others are inputs
}



void loop() {
  static int track_pos = -1;
  static int track[256];//= {660, 660, 660, 510, 660, 770, 380, 510, 380, 320, 440, 480, 450, 430, 380, 660, 760, 860, 700, 760, 660, 520, 580, 480}; //mario, 23 track_pos
  int freq = check_button();
  
  if(freq<=-10 && freq>=-20){play_track(track, track_pos, freq);}
  else if(freq==-2 && track_pos>=0){tone(2, track[track_pos], 50); track_pos--; delay(50);}
  else if(track_pos!=255 && freq>=0){track_pos++; track[track_pos] = freq; tone(2, track[track_pos], 50); delay(50);}
  else{}
}



void play_track(int track[], int track_pos, int filter_type){
  //unsigned char tone_length = 160;
  for(int i=0; i<=track_pos; i++){
    int note;
    
      if(filter_type==-10){note = track[i];}
      else if(filter_type==-11){
        if(i!=0 || i!=track_pos){note = ((track[i-1]+track[i]+track[i+1])/3);}
        else if(i==0){note = track[i];}
        else{note = track[i];}
        }
      
    int tone_length = (analogRead(A0)/5)+100;
    tone(2, note, tone_length); delay(tone_length);
    while(digitalRead(5)==HIGH){i=track_pos;} //stops playing track if play button is pressed
  }
}



int check_button(void){
  int freq;
  static char octave = 4;
  bool add = digitalRead(3);
  bool delete1 = digitalRead(4);
  bool play = digitalRead(5);
  bool octave_change = digitalRead(6);
  
  if(octave_change==HIGH){
    octave = (analogRead(A0)*8)/1025;
    for(int i=1; i<=3; i++){tone(2, 200*(octave+1), 100); delay(150);}
  }
  else if(add==HIGH){freq = freq_note_map(octave); delay(100);} //add tone button
  else if(delete1==HIGH){freq = -2; delay(100);} //delete button
  else if(play==HIGH){ //play track button, no filter is freq = -10, smooth filter is freq = -11
    int filter_type = (analogRead(A0)*2)/1025;
      if(filter_type==0){freq = -10;}
      else{freq = -11;}
      delay(100);
  }
  else{freq = -100;} //no button pressed
  
  return freq;
}



int freq_note_map(char octave){
  int freq = analogRead(A0);
  int mult = 1;
  const float notes[8] = {0, 16.35, 18.35, 20.6, 21.83, 24.5, 27.5, 30.87}; //notes in octave 0 including rest----- rest,C,D,E,F,G,A,B
  
  for(int i=1; i<=octave; i++){mult = mult*2;} //octave multiplier
  freq = notes[(freq*8)/1025]*mult; //1025 so it never goes does note[8] which does not exist
  
  return freq;
}


