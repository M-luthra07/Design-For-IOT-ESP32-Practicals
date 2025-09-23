#include <Arduino.h>
#include <WiFi.h>
#include <ESP_Mail_Client.h>

// Replace with your WiFi credentials
#define WIFI_SSID "Galaxy A23 9112"
#define WIFI_PASSWORD "bhuj4849"

// Gmail SMTP settings
#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465

// Sender credentials (use new Gmail + App Password)
#define AUTHOR_EMAIL "designforiot1234@gmail.com"
#define AUTHOR_PASSWORD "ofmk hbxk mbdr hyoh"

// Recipient email
#define RECIPIENT_EMAIL "manya22csu458@ncuindia.edu"

// Global SMTP session object
SMTPSession smtp;

// Callback to show status
void smtpCallback(SMTP_Status status);

void setup() {
  Serial.begin(115200);
  Serial.println("Connecting to WiFi...");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  Serial.println(WiFi.localIP());

  // Enable network reconnect
  MailClient.networkReconnect(true);

  // Debug level (1 = basic)
  smtp.debug(1);

  // Set callback
  smtp.callback(smtpCallback);

  // Configure SMTP session
  Session_Config config;
  config.server.host_name = SMTP_HOST;
  config.server.port = SMTP_PORT;
  config.login.email = AUTHOR_EMAIL;
  config.login.password = AUTHOR_PASSWORD;
  config.login.user_domain = "";

  // NTP Time
  config.time.ntp_server = F("pool.ntp.org,time.nist.gov");
  config.time.gmt_offset = 5.5; // India = GMT+5:30
  config.time.day_light_offset = 0;

  // Create email message
  SMTP_Message message;
  message.sender.name = F("ESP32 Mailer");
  message.sender.email = AUTHOR_EMAIL;
  message.subject = F("ESP32 Test Email");
  message.addRecipient(F("Receiver"), RECIPIENT_EMAIL);

  // Send raw text
  String textMsg = "Hello, this is a test email sent from ESP32!";
  message.text.content = textMsg.c_str();
  message.text.charSet = "us-ascii";
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

  // You can also send HTML (uncomment below)
  /*
  String htmlMsg = "<h2 style=\"color:blue;\">Hello from ESP32</h2><p>This is a test HTML email</p>";
  message.html.content = htmlMsg.c_str();
  message.html.charSet = "us-ascii";
  message.html.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
  */

  // Priority + notification
  message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_low;
  message.response.notify = esp_mail_smtp_notify_success |
                            esp_mail_smtp_notify_failure |
                            esp_mail_smtp_notify_delay;

  // Connect & send
  if (!smtp.connect(&config)) {
    Serial.println("Connection failed!");
    return;
  }

  if (!MailClient.sendMail(&smtp, &message)) {
    Serial.print("Error sending Email, Reason: ");
    Serial.println(smtp.errorReason());
  }
}

void loop() {
  // Nothing in loop
}

// Callback function to check status
void smtpCallback(SMTP_Status status) {
  Serial.println(status.info());

  if (status.success()) {
    Serial.println("Email sent successfully!");
  } else {
    Serial.println("Email sending failed.");
  }
}