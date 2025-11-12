# November 8, 2025
# Runs MediaPipe and stores coordinate data into a csv for model training

import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, classification_report
import joblib
import warnings
warnings.filterwarnings('ignore')

# load data from csv
FILENAME = "asl_data.csv"
data = pd.read_csv(FILENAME)
print(data.head())

# format data
X = data.drop('label', axis = 1)
y = data['label']

# split data into train (80%) and test data (20%)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# create the Random Forest Classifier (ML Tool)
rf_classifier = RandomForestClassifier(n_estimators=100, random_state=42)
rf_classifier.fit(X_train, y_train)

# check accuracy and print report
y_pred = rf_classifier.predict(X_test)
accuracy = accuracy_score(y_test, y_pred)
classification_rep = classification_report(y_test, y_pred)

print(f"Accuracy: {accuracy:.2f}")
print("\nClassification Report:\n", classification_rep)

sample = X_test.iloc[0:1]
prediction = rf_classifier.predict(sample)
true_label = y_test.iloc[0]
print(f"Actual Letter: {true_label}")
print(f"Predicted Letter: {prediction[0]}")

sample_dict = sample.iloc[0].to_dict()
print(f"\nSample Hand Coordinates: {sample_dict}")
print(f"Predicted Letter: {prediction[0]}")

# save model
rf_classifier_FILENAME = "asl_model.pkl"
joblib.dump(rf_classifier, rf_classifier_FILENAME)
print(f"\nModel saved to {rf_classifier_FILENAME}")