import SwiftUI
import SwiftData

let columnWidth: CGFloat = 450

struct ContentView<Manager: NEManagerProtocol>: View {
    var body: some View {
        TabView {
            DashboardView<Manager>()
                .tabItem {
                    Image(systemName: "list.bullet.below.rectangle")
                    Text("main.dashboard")
                }
            LogView()
                .tabItem {
                    Image(systemName: "rectangle.and.text.magnifyingglass")
                    Text("logging")
                }
            SettingsView<Manager>()
                .tabItem {
                    Image(systemName: "gearshape")
                        .environment(\.symbolVariants, .none)
                    Text("settings")
                }
        }
    }
}

struct MainView_Previews: PreviewProvider {
    static var previews: some View {
        @StateObject var manager = MockNEManager()
        ContentView<MockNEManager>()
            .modelContainer(
                try! ModelContainer(
                    for: Schema([ProfileSummary.self, NetworkProfile.self]),
                    configurations: ModelConfiguration(
                        isStoredInMemoryOnly: true
                    )
                )
            )
            .environmentObject(manager)
        ContentView<MockNEManager>()
            .modelContainer(
                try! ModelContainer(
                    for: Schema([ProfileSummary.self, NetworkProfile.self]),
                    configurations: ModelConfiguration(
                        isStoredInMemoryOnly: true
                    )
                )
            )
            .environmentObject(manager)
            .previewInterfaceOrientation(.landscapeLeft)
    }
}
