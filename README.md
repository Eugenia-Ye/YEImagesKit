# YEImagesKit ![App Icon](https://github.com/Eugenia-Ye/YEImagesKit/blob/master/YEImagesKit/Recourse/Images.xcassets/AppIcon.appiconset/Icon_32%402x.png)
A Mac app for checking Xcode projects for unused resources

# Why we need it ?

As we know, the **longer** the development of a project, the **more** functional modules will be added.  Accordingly, the **more** pictures and other resources will be introduced in the project. 

However, when removing some modules that are no longer in use, developers tend to forget to delete the corresponding picture resources for the module because the source and the resource are separate. As the time goes, there will be a large number of resources that are not used in the project.

Our solution maybe nothing more than, individually copy the resource file name, and then look up the string in the XCode globally. If not found, then the resources may "**possibly**" not been used any more. 

**Why is it possible?** Because in the code, it is possible that some resource name "sneak" because their name strings are constructed by string format. In this situation there is no way to find out all matching resource names.

So, we need such a tool: to quickly find all the resources in the project did not use the file.

Here is a **script** someone may choose in their project.
![script](https://github.com/Eugenia-Ye/YEImagesKit/blob/master/script.png)

But its **shortcomings** are obvious: 
 - not smart enough
 - not common enough
 - too slow

The results are not always reliable. If you delete resource files based on the result of this script, you may have a high risk to discard files that are really useful in the project.

# Why choose YEImageKit ?

YEImageKit provides an interface to end users. User can easily configure script's arguments, and then show the result in a clear comparison panel. It is more user-friendly.
And the tool has been optimised on the core code to make it a great improvement in search efficiency and the correctness of the results.

The core steps are outlined below:
**Find**: All resources under the selected directory. There is no much difference from Unused in this step. App calls find command to find the specified suffix name of the file.

**Match**: Unlike the above scenario, App did not full-text search for each resource file name because there was too much resources in the project, which would result in a dramatical decline in performance. So I improve it by searching just for the source code, Xib, Storyboard and plist and other documents. First, full-text search the strings which may be referred as resource, and then try to match the resource file name with these strings.

## Usage

It's an useful utility tool to check what resources are not being used in your Xcode projects. Very easy to use: 

1. Click `Browse..` to select a project folder.
2. Click `Search` to start searching.
3. Wait a second, the results will be shown in the tableview.

## Demo
![Demo](https://github.com/Eugenia-Ye/YEImagesKit/blob/master/YEImageKitDemo.gif)


## Feature

Check `Ignore similar name` to ignore the resources which referenced by string concatenation.

For example:

You import some resources like:

```
icon_tag_0.png
icon_tag_1.png
icon_tag_2.png
icon_tag_3.png
```

And using in this way:

```
	NSInteger index = random() % 4;
	UIImage *img = [UIImage imageNamed:[NSString stringWithFormat:@"icon_tag_%d", index]];
```

`icon_tag_x.png` should not be shown as unused resource, we should ignore them.

## Installation

* Download: [YEImagesKit.app.zip](https://github.com/Eugenia-Ye/YEImagesKit/tree/master/Release/YEImagesKit.app.zip)
* Or build and run the project using XCode.

## Requirements

Requires OS X 10.7 and above, ARC.
