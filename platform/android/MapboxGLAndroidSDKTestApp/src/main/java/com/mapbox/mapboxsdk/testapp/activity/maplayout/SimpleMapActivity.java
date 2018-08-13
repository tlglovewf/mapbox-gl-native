package com.mapbox.mapboxsdk.testapp.activity.maplayout;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;

import com.mapbox.mapboxsdk.camera.CameraPosition;
import com.mapbox.mapboxsdk.camera.CameraUpdate;
import com.mapbox.mapboxsdk.camera.CameraUpdateFactory;
import com.mapbox.mapboxsdk.geometry.LatLng;
import com.mapbox.mapboxsdk.geometry.LatLngBounds;
import com.mapbox.mapboxsdk.maps.MapView;
import com.mapbox.mapboxsdk.maps.MapboxMap;
import com.mapbox.mapboxsdk.testapp.R;


/**
 * Test activity showcasing a simple MapView without any MapboxMap interaction.
 */
public class SimpleMapActivity extends AppCompatActivity {

  private MapView mapView;

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_map_simple);

    mapView = (MapView) findViewById(R.id.mapView);
    mapView.onCreate(savedInstanceState);


    mapView.LoadStyleJson("/sdcard/v2xdemostyle.json");

    Button btn = new Button(this);

    btn.setText("点击");
    btn.setLayoutParams(new ViewGroup.LayoutParams(
            ViewGroup.LayoutParams.WRAP_CONTENT,
            ViewGroup.LayoutParams.WRAP_CONTENT));

    this.mapView.addView(btn);

    btn.setOnClickListener(new View.OnClickListener() {

      @Override
      public void onClick(View arg0) {
//        CameraPosition pos = new CameraPosition.Builder()
//                .target(new LatLng(31.4919552, 120.2865664)) // Sets the new camera position
//                .zoom(10) // Sets the zoom to level 10
//                .tilt(20) // Set the camera tilt to 20 degrees
//                .build();

        MapboxMap map = mapView.getMapboxMap();
        if( map != null ) {
          LatLng lonlat = new LatLng(31.4919552, 120.2865664);

          CameraPosition cpos = map.getCameraPosition();

          CameraPosition pos = new CameraPosition(lonlat, 10, cpos.tilt, cpos.bearing);

          map.setCameraPosition(pos);
        }

      }
    });
  }

  @Override
  protected void onStart() {
    super.onStart();
    mapView.onStart();
  }

  @Override
  protected void onResume() {
    super.onResume();
    mapView.onResume();
  }

  @Override
  protected void onPause() {
    super.onPause();
    mapView.onPause();
  }

  @Override
  protected void onStop() {
    super.onStop();
    mapView.onStop();
  }

  @Override
  public void onLowMemory() {
    super.onLowMemory();
    mapView.onLowMemory();
  }

  @Override
  protected void onDestroy() {
    super.onDestroy();
    mapView.onDestroy();
  }

  @Override
  protected void onSaveInstanceState(Bundle outState) {
    super.onSaveInstanceState(outState);
    mapView.onSaveInstanceState(outState);
  }
}
