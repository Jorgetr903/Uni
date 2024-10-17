


/*using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;*/

public class CodigoPantallaCompleta : MonoBehaviour {
    public Toggle toggle;
    public TMP_Dropdown resolucionesDropdown;
    Resolucion[] resoluciones;

    // Start is called before the first frame update
    void Start() {
        if (Screen.fullScreen) {
            toggle.isOn = true;
        }
        else {
            toggle.isOn = false;
        }

        RevisarResolucion();
    }

    public void ActivarPantallaCompleta(bool pantallaCompleta) {
        Screen.fullScreen = pantallaCompleta;
    }

    public void RevisarResolucion() {
        resoluciones = Screen.resolutions;
        resolucionesDropdown.ClearOptions();
        List<string> opciones = new List<string>();
        int resolucionActual = 0;

        for (int i = 0; i < resoluciones.length; i++) {
            string opcion = resoluciones[i].width + " x " + resoluciones[i].height;
            opciones.Add(opcion);

            if (Screen.fullScreen && resoluciones[i].width == Screen.currentResolution.width &&
                resoluciones[i].height == Screen.currentResolution.height) {
                resolucionActual = i;
            }
        }
        resolucionesDropdown.AddOptions(opciones);
        resolucionesDropdown.value = resolucionActual;
        resolucionesDropdown.RefreshShowValue();

        resolucionesDropdown.value = PlayerPrefs.GetInt("numeroResolucion", 0);
    }

    public void CambiarResolucion(int indiceResolucion) {
        PlayerPrefs.SetInt("numeroResolucion", resolucionesDropdown.value);
        Resolution resolucion = resoluciones[indiceResolucion];
        Screen.SetResolution(resolucion.width, resolucion.height, Screen.fullScreen);
    }
}
