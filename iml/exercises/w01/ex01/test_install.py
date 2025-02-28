"""
Test the python installation.
"""

def main():
    # Verify that each package is installed
    try:
        import numpy as np

        array = np.arange(10)
        array = np.eye(len(array)) @ array
    except Exception as err:
        print(f"Error with numpy:\n{type(err).__name__}: {err}")
    
    try:
        import matplotlib.pyplot as plt
        
        fig = plt.figure()
        ax = fig.add_subplot(111)
        ax.plot([0, 1, 2], [0, 1 ,2])
        plt.close(fig)
    except Exception as err:
        print(f"Error with matplotlib:\n{type(err).__name__}: {err}")
    
    try:
        from PIL import Image

        image = Image.open("img/krabby_patty.jpg")
        image.convert("L")
    except Exception as err:
        print(f"Error with Pillow:\n{type(err).__name__}: {err}")
    
    try:
        import sklearn
        from sklearn.svm import SVC

        svm = SVC()
        X, y = [[-1], [1]], [-1, 1]
        svm.fit(X, y)
    except Exception as err:
        print(f"Error with sklearn:\n{type(err).__name__}: {err}")
    
    try:
        import torch
        import torchvision
        from torchvision.transforms import CenterCrop

        tensor = torch.rand(5, 5)
        tensor = torch.eye(len(tensor)) @ tensor
        crop = CenterCrop(3)
        tensor = crop(tensor)
    except Exception as err:
        print(f"Error with pytorch:\n{type(err).__name__}: {err}")
    
    try:
        from torchinfo import summary
    except Exception as err:
        print(f"Error with torchinfo:\n{type(err).__name__}: {err}")


if __name__ == "__main__":
    main()
