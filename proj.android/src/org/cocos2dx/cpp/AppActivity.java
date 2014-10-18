/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/
package org.cocos2dx.cpp;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import com.ktplay.open.KTPlay;

import android.app.AlertDialog.Builder;
import android.content.DialogInterface;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;

public class AppActivity extends Cocos2dxActivity {

	public static Handler handler;

	public static void exitGame() {
		Message message = Message.obtain();
		message.what = 1;
		handler.sendMessage(message);
	}
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		
		super.onCreate(savedInstanceState);
		
		KTPlay.startWithAppKey(this, "js31bM", "43fc2d50fe5bc63779dd33697b7b1d4f30f31d76");
		
		handler = new Handler(){

			@Override
			public void handleMessage(Message msg) {
				switch (msg.what) {
				case 1:
					
					Builder builder = new Builder(AppActivity.this);
					builder.setTitle("Are you want to exit")
					.setPositiveButton("Exit", 
							 new DialogInterface.OnClickListener() {
								
								@Override
								public void onClick(DialogInterface dialog, int which) {
									// TODO 自动生成的方法存根
									System.exit(0);
								}
							})
					.setNegativeButton("No", null)
					.show();
			
					break;

				default:
					break;
				}
			}
			
		};
	}
	
	
	@Override
	protected void onResume() {
		// TODO 自动生成的方法存根
		super.onResume();

		KTPlay.onPause(this);
	}

	@Override
	protected void onPause() {
		// TODO 自动生成的方法存根
		super.onPause();
		
		KTPlay.onResume(this);
	}

	@Override
	public Cocos2dxGLSurfaceView onCreateView() {
		// TODO 自动生成的方法存根
		
		Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
		
		// Create stencil buffer
		glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
		
		return glSurfaceView;
	}
	
	
	static {
		System.loadLibrary("KTPlay");
		System.loadLibrary("KTAccountmanager");
		System.loadLibrary("KTFriendship");
		System.loadLibrary("KTLeaderboard");
		System.loadLibrary("cocos2dcpp");
	}

}
