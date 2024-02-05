import matplotlib.pyplot as plt
import pandas as pd
from sklearn.tree import DecisionTreeClassifier
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder
from sklearn import tree
from sklearn import metrics

col_names = ['Age', 'Gender', 'Smoking', 'Hx Smoking', 'Hx Radiothreapy', 'Thyroid Function', 'Physical Examination', 'Adenopathy',	'Pathology', 'Focality', 'Risk', 'T', 'N', 'M',	'Stage', 'Response', 'Recurred']
pima = pd.read_csv("Thyroid_Diff.csv")
pima.columns = col_names

pima['Age'] = pd.to_numeric(pima['Age'], errors='coerce')
binary_map = {'Yes': 1, 'No': 0, 'F': 0, 'M': 1}
pima['Gender'] = pima['Gender'].map(binary_map)
pima['Smoking'] = pima['Smoking'].map(binary_map)
pima['Hx Smoking'] = pima['Hx Smoking'].map(binary_map)
pima['Hx Radiothreapy'] = pima['Hx Radiothreapy'].map(binary_map)
pima['Recurred'] = pima['Recurred'].map(binary_map)
print(pima.head())

label_encoders = {}
for column in ['Thyroid Function', 'Physical Examination', 'Adenopathy', 'Pathology', 'Focality']:
    le = LabelEncoder()
    pima[column] = le.fit_transform(pima[column])
    label_encoders[column] = le

feature_cols = ['Age', 'Smoking', 'Hx Smoking', 'Hx Radiothreapy', 'Thyroid Function', 'Physical Examination', 'Adenopathy', 'Pathology', 'Focality']
X = pima[feature_cols]
y = pima.Recurred
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=1)

clf = DecisionTreeClassifier(criterion='entropy')
clf = clf.fit(X_train,y_train)
print("Testing:")
print(X_test.head())
y_pred = clf.predict(X_test)
print("Accuracy:",metrics.accuracy_score(y_test, y_pred))

plt.figure(figsize=(15,8))
tree.plot_tree(clf, filled=True, rounded=True, max_depth=4, fontsize=8, feature_names=feature_cols,class_names=['0','1'])
plt.title("Decision tree trained on all features")
plt.show()