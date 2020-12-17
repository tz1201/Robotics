import processing.serial.*;
import processing.opengl.*;
import javax.swing.JFileChooser;
import ddf.minim.analysis.*;
import ddf.minim.effects.*;
import ddf.minim.signals.*;
import ddf.minim.*;

PitchDetectorFFT PD; // Naive
AudioSource AS;
Minim minim;
BeatDetect beat;
AudioInput in;
Serial myPort;

float []freq_buffer = new float[10];
float []sorted;
int freq_buffer_index = 0;
int state = 0; //0 represents slow, 1 represent it is too fast, 2 represents too slow

long last_t = -1;
float avg_level = 0;
float last_level = 0;
float begin_playing_time = -1;
int pitch;

float eRadius;
int lastTime = 0;
int currentTime;
int count = 0;

void setup()
{
  //bluetooth connection
  //printArray(Serial.list());
  //myPort = new Serial(this, Serial.list()[ 5 ], 9600);
  size(200, 200, P3D);
  minim = new Minim(this);
  minim.debugOn();
  AS = new AudioSource(minim);
  AS.OpenMicrophone();
  PD = new PitchDetectorFFT();
  PD.ConfigureFFT(2048, AS.GetSampleRate());
  PD.SetSampleRate(AS.GetSampleRate());
  AS.SetListener(PD);
  
  beat = new BeatDetect();
  ellipseMode(RADIUS);
  eRadius = 20;
  in = minim.getLineIn(Minim.STEREO, 2048);
}


void draw()
{
  background(0);
  beat.detect(in.mix);
  float a = map(eRadius, 20, 80, 60, 255);
  fill(60, 255, 0, a);
  
    if (begin_playing_time == -1)
  begin_playing_time = millis();

  float f = 0;
  float level = AS.GetLevel();
  long t = PD.GetTime();
  if (t == last_t) return;
  last_t = t;
  f = PD.GetFrequency();
  avg_level = level;
  last_level = f;
  
  if ( beat.isOnset() ){
    currentTime = millis();
    if ((currentTime - lastTime)<2000){
      count += 1;
      if (count > 5){
        println(currentTime,"fast");
        count = 0;
      }
    }
    else{
      count -= 1;
      if (count<=0){
        count = 0;
      }
    }
    
    lastTime = currentTime;
    eRadius = 80;
  } 
  ellipse(width/2, height/2, eRadius, eRadius);
  eRadius *= 0.95;
  if ( eRadius < 20 ) eRadius = 20;
// beat detection end  

  if (f >= 257 && f <= 260){
    println("C");
    //myPort.write('C');
  }
  else if (f >= 288 && f <= 293){
    //myPort.write('D');
    println('D');
  }
  else if (f >= 320 && f <= 340){
    //myPort.write('E');
    println("E");
  }
  else if ((f >= 170 && f <= 185) || (f >= 350 && f <= 360)){
    //myPort.write("F");
    println("F");
  }
  else if (f >= 190 && f <= 197){
    //myPort.write('G');
    println("G");
  }
  else if (f >= 210 && f <= 220){
    //myPort.write('A');
    println("A");
  }
  else if (f >= 245 && f <= 250){
    //myPort.write('B');
    println("B");
  }
  
}

void stop()
{
  AS.Close();

  minim.stop();

  super.stop();
}

//beat detection
// for bluetooth sending
