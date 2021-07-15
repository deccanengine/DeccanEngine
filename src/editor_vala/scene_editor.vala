namespace Deccan {
    class SceneEditorWindow : Gtk.ApplicationWindow {
        internal SceneEditorWindow(Gtk.Application app) {
            GLib.Object(application: app, title: "Deccan Scene Editor");

            this.window_position = Gtk.WindowPosition.CENTER;
            this.set_default_size(1280, 800);
        }
    }

    public class SceneEditorApplication : Gtk.Application {
        private const GLib.ActionEntry[] _actions_file_menu = {
            { "menu-file", null },
            { "new-scene",  on_new_scene_cb },
            { "open-scene", on_open_scene_cb },
            { "save-scene", on_save_scene_cb },
            { "quit", on_quit_cb },
        };

        internal SceneEditorApplication() {
            GLib.Object(application_id: "org.deccan.sceneeditor");
        }

        protected override void activate() {
            new SceneEditorWindow(this).show_all();
        }

        protected override void startup() {
            base.startup();

            var builder  = new Gtk.Builder.from_file("resources/menubar.ui");
            this.menubar = builder.get_object("menubar") as GLib.MenuModel;

            this.add_action_entries(_actions_file_menu, this);
        }

        private void on_new_scene_cb(GLib.SimpleAction action, GLib.Variant? arg) {
        }

        private void on_open_scene_cb(GLib.SimpleAction action, GLib.Variant? arg) {
        }

        private void on_save_scene_cb(GLib.SimpleAction action, GLib.Variant? arg) {
        }

        private void on_quit_cb(GLib.SimpleAction action, GLib.Variant? arg) {
            this.quit();
        }
    }
}
