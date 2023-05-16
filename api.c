/******************************************************************************/
/*                                                                            */
/*                          API Server Hello Name                             */
/*                                                                            */
/* But:                                                                       */
/*  Crée un serveur API simple utilisant la bibliothèque libmicrohttpd        */
/*                                                                            */
/* Instalation:                                                               */
/*  apt install libmicrohttpd-dev                                             */
/*                                                                            */
/* Compilation:                                                               */
/*  gcc -o api api.c -lmicrohttpd                                             */
/*                                                                            */
/* Utilisation:                                                               */
/*  - Lancer l'exécutable 'api'                                               */
/*  - Le serveur sera disponible sur le port 8080                             */
/*  - Lorsqu'une requête POST est reçue sur l'URL '/hello' avec le            */
/*    paramètre 'name', le serveur répondra avec "Hello" et le paramètre      */
/*    'name' s'il est présent, sinon il répondra avec "Hello unknown"         */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

static int hello_handler(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **ptr)
{
    if (strcmp(method, "POST") == 0 && strcmp(url, "/hello") == 0)
    {
        // Analyse des paramètres de l'URL
        struct MHD_PostProcessor *pp = MHD_create_post_processor(connection, 1024,
                                                                  &MHD_post_process,
                                                                  (void *)"hello");
        MHD_post_process(pp, upload_data, *upload_data_size);

        // Récupération du paramètre 'name'
        const char *name = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "name");

        // Réponse avec "Hello" et le paramètre 'name'
        char response[1024];
        if (name && *name != '\0') {
            snprintf(response, sizeof(response), "Hello %s", name);
        } else {
            snprintf(response, sizeof(response), "Hello unknown");
        }

        struct MHD_Response *http_response = MHD_create_response_from_buffer(strlen(response),
                                                                             (void *)response,
                                                                             MHD_RESPMEM_MUST_COPY);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, http_response);
        MHD_destroy_response(http_response);

        return ret;
    }

    // Si l'URL ou la méthode ne correspondent pas, renvoyer une erreur 404
    struct MHD_Response *http_response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, http_response);
    MHD_destroy_response(http_response);

    return ret;
}

int main()
{
    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION, 8080, NULL, NULL,
                                                &hello_handler, NULL, MHD_OPTION_END);
    if (daemon == NULL)
    {
        printf("Erreur lors du démarrage du serveur\n");
        return 1;
    }

    printf("Serveur en cours d'exécution sur le port 8080...\n");

    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}
