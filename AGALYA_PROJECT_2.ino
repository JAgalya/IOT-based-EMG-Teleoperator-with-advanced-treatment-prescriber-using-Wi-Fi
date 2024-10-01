const int emgPin = A0; // Analog pin for EMG signal
const int numSamples = 15; // Number of samples to average
const int sampleInterval = 1000; // Sampling interval in milliseconds (1 second)
int emgSamples[numSamples];
int sampleIndex = 0;
float averageAmplitude = 0;
int sampleCount = 0;

// Define threshold values
const float lowThreshold = 20.0; // Abnormally low threshold in mV
const float moderateThreshold = 30.0; // Moderate threshold in mV
const float higherThreshold = 50.0; // Higher threshold in mV

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (sampleCount < numSamples) {
    // Acquire EMG samples
    int emgValue = analogRead(emgPin);
    emgSamples[sampleIndex] = emgValue;
    sampleIndex = (sampleIndex + 1) % numSamples;
    sampleCount++;

    // Print each amplitude value
    Serial.print("Amplitude (mV): ");
    float amplitude_mV = emgValue * (5.0 / 1024.0); // Convert to mV
    Serial.println(amplitude_mV);

    // Calculate average amplitude after 15 samples
    if (sampleCount == numSamples) {
      averageAmplitude = calculateAverageAmplitude();
      
      // Print average amplitude
      Serial.print("Average Amplitude (mV): ");
      Serial.println(averageAmplitude);
      
      // Determine treatment suggestion and pain intensity
      if (averageAmplitude < lowThreshold) {
        Serial.println("Treatment: Normal");
        Serial.println("Pain Intensity: 0");
      } else if (averageAmplitude >= lowThreshold && averageAmplitude < moderateThreshold) {
        Serial.println("Treatment: Ultrasound Therapy");
        Serial.println("Pain Intensity: Low");
      } else if (averageAmplitude >= moderateThreshold && averageAmplitude < higherThreshold) {
        Serial.println("Treatment: Shortwave Diathermy");
        Serial.println("Pain Intensity: Moderate");
      } else if (averageAmplitude >= higherThreshold) {
        Serial.println("Treatment: Electrical Stimulator");
        Serial.println("Pain Intensity: High");
      }
    }
  
    // Delay for the sampling interval
    delay(sampleInterval);
  }
}

float calculateAverageAmplitude() {
  float sum = 0;
  for (int i = 0; i < numSamples; i++) {
    sum += emgSamples[i];
  }
  return (sum / numSamples) * (5.0 / 1024.0); // Convert to mV
}
