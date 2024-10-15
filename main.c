#include <poppler/glib/poppler.h>
#include <stdio.h>



int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s input.pdf output.txt\n", argv[0]);
        return 1;
    }

    const char *input_file = argv[1];
    const char *output_file = argv[2];

    GError *error = NULL;

    // Open the PDF document
    PopplerDocument *doc = poppler_document_new_from_file(input_file, NULL, &error);
    if (!doc) {
        fprintf(stderr, "Failed to open PDF: %s\n", error->message);
        g_error_free(error);
        return 1;
    }

    FILE *out = fopen(output_file, "w");
    if (!out) {
        fprintf(stderr, "Failed to open output file: %s\n", output_file);
        g_object_unref(doc);
        return 1;
    }

    int num_pages = poppler_document_get_n_pages(doc);
    for (int i = 0; i < num_pages; ++i) {
        // Get the page
        PopplerPage *page = poppler_document_get_page(doc, i);
        if (!page) {
            fprintf(stderr, "Failed to read page %d\n", i + 1);
            continue;
        }

        // Extract the text from the page
        char *text = poppler_page_get_text(page);
        fprintf(out, "Page %d:\n%s\n", i + 1, text);

        // Clean up
        g_free(text);
        g_object_unref(page);
    }

    fclose(out);
    g_object_unref(doc);

    printf("Text extraction completed successfully.\n");
    return 0;
}
