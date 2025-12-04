import pandas as pd
import matplotlib.pyplot as plt
df = pd.read_csv("L2cleaned.csv")

df.drop(df[df['Time(ms)'] <= 360000].index, inplace=True)
df.drop(df[df['Time(ms)'] >= 400000].index, inplace=True)

df.plot( x = 'Time(ms)', y = 'Temperature(C)', label = "Temperature")
df.plot( x = 'Time(ms)', y = 'Pressure(Pa)', label = "Pressure")
df.plot( x = 'Time(ms)', y = 'ABS Altitude(m)', label = "ABS Altitude")
df.plot( x = 'Time(ms)', y = 'Rel Altitude(m)', label = "Rel Altitude(m)")


plt.legend()
plt.show()

print(df['Rel Altitude(m)'].max())



