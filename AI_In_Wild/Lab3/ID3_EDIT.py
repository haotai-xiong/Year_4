import matplotlib.pyplot as plt
import pandas as pd
from sklearn.tree import DecisionTreeClassifier
from sklearn.model_selection import train_test_split
from sklearn import tree
from sklearn import metrics

col_names = ['pregnant', 'glucose', 'bp', 'skin', 'insulin', 'bmi', 'pedigree', 'age', 'label']
pima = pd.read_csv("diabetes.csv", header=None, names=col_names)

feature_cols = ['pregnant', 'insulin', 'bmi', 'age', 'glucose', 'bp', 'pedigree']
X = pima[feature_cols]
y = pima.label

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=1)

clf = DecisionTreeClassifier(criterion='entropy')
clf = clf.fit(X_train, y_train)

def predict_diabetes(new_patient_data):
    new_patient_df = pd.DataFrame([new_patient_data], columns=feature_cols)
    prediction = clf.predict(new_patient_df)
    return "Diabetes" if prediction[0] == 1 else "No Diabetes"

def get_new_patient_data():
    print("Please enter the following data for the new patient.")
    pregnant = float(input("Number of pregnancies (0-17): "))
    insulin = float(input("2-Hour serum insulin (mu U/ml) (0-846): "))
    bmi = float(input("Body mass index (weight in kg/(height in m)^2) (0-67): "))
    age = float(input("Age (years) (21-81): "))
    glucose = float(input("Plasma glucose concentration a 2 hours in an oral glucose tolerance test (0-199): "))
    bp = float(input("Diastolic blood pressure (mm Hg) (0-122): "))
    pedigree = float(input("Diabetes pedigree function (0.078-2.42): "))
    return [pregnant, insulin, bmi, age, glucose, bp, pedigree]

new_patient = get_new_patient_data()
prediction_result = predict_diabetes(new_patient)
print("Prediction for the new patient:", prediction_result)