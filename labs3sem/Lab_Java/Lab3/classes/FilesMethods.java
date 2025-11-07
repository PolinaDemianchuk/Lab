package classes;

import abstractclasses.AbsList;
import classes.CoffeeMachineNotAbstr;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import java.io.*;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;

public class FilesMethods
{
    private final SimpleDateFormat dateFormat = new SimpleDateFormat("dd.MM.yyyy");

    public void exportToTxt(List<CoffeeMachineNotAbstr> machines, String filename)
    {
        try (FileWriter writer = new FileWriter(filename))
        {
            Iterator<CoffeeMachineNotAbstr> it = machines.iterator();
            while (it.hasNext())
            {
                CoffeeMachineNotAbstr machine = it.next();
                writer.write(machine.getId() + " || " +
                        machine.getType() + " || " +
                        machine.getModel() + " || " +
                        machine.getPower() + " || " +
                        machine.getMaxCoffeeCapacity() + " || " +
                        machine.getMaxWaterCapacity() + " || " +
                        dateFormat.format(machine.getManufactureDate()) + " || " +
                        machine.getPrice() + "\n");
            }
            System.out.println("Saved " + machines.size() + " machines to "+ filename);
        } catch (IOException e)
        {
            System.out.println("Error saving file: " + e.getMessage());
        }
    }

    public List<CoffeeMachineNotAbstr> importFromTxt(String filename)
    {
        List<CoffeeMachineNotAbstr> machines = new ArrayList<>();
        try (Scanner fileScanner = new Scanner(new FileReader(filename)))
        {
            while (fileScanner.hasNextLine())
            {
                String line = fileScanner.nextLine();
                if (line.isEmpty()) continue;

                String[] elems = line.split(",");
                if (elems.length == 8) {
                    try {
                        int id = Integer.parseInt(elems[0]);
                        String type = elems[1];
                        String model = elems[2];
                        int power = Integer.parseInt(elems[3]);
                        int coffeeCap = Integer.parseInt(elems[4]);
                        int waterCap = Integer.parseInt(elems[5]);
                        Date date = dateFormat.parse(elems[6]);
                        double price = Double.parseDouble(elems[7]);

                        CoffeeMachineNotAbstr machine = new CoffeeMachineNotAbstr(
                                id, type, model, power, coffeeCap, waterCap, date, price);
                        machines.add(machine);

                    } catch (Exception e)
                    {
                        System.out.println("Error parsing line" + e.getMessage());
                    }
                }
            }
            System.out.println("Loaded " + machines.size() + " machines from file " + filename);
        } catch (IOException e) {
            System.out.println("Error loading file " + e.getMessage());
        }
        return machines;
    }


    public void exportToJSON(List<CoffeeMachineNotAbstr> machines, String filename) {
        try {
            JSONArray machinesArray = new JSONArray();
            Iterator<CoffeeMachineNotAbstr> it = machines.iterator();

            while (it.hasNext()) {
                CoffeeMachineNotAbstr machine = it.next();
                JSONObject machineJson = new JSONObject();
                machineJson.put("id", machine.getId());
                machineJson.put("type", machine.getType());
                machineJson.put("model", machine.getModel());
                machineJson.put("power", machine.getPower());
                machineJson.put("maxCoffeeCapacity", machine.getMaxCoffeeCapacity());
                machineJson.put("maxWaterCapacity", machine.getMaxWaterCapacity());
                machineJson.put("created", dateFormat.format(machine.getManufactureDate())); // "created" в другом методе
                machineJson.put("price", machine.getPrice());
                machinesArray.add(machineJson);
            }

            JSONObject j = new JSONObject();
            j.put("coffeeMachines", machinesArray);

            try (PrintWriter out = new PrintWriter(new FileWriter(filename))) {
                out.write(j.toString());
                System.out.println("Exported " + machines.size() + " machines to " + filename);
            }
        } catch (Exception e) {
            System.out.println("Error exporting to JSON: " + e.getMessage());
        }
    }

    public List<CoffeeMachineNotAbstr> importFromJSON(String filename)
    {
        List<CoffeeMachineNotAbstr> machines = new ArrayList<>();
        JSONParser parser = new JSONParser();

        try (FileReader reader = new FileReader(filename))
        {
            Object obj = parser.parse(reader);
            JSONObject JsonFile = (JSONObject) obj;
            JSONArray machinesArray = (JSONArray) JsonFile.get("coffeeMachines");
            int count = 0;

            Iterator<Object> it = machinesArray.iterator();
            while (it.hasNext()) {
                Object item = it.next();
                JSONObject machineJson = (JSONObject) item;
                try {
                    int id = Integer.parseInt(machineJson.get("id").toString());
                    String type = (String) machineJson.get("type");
                    String model = (String) machineJson.get("model");
                    int power = Integer.parseInt(machineJson.get("power").toString());
                    int maxCoffeeCapacity = Integer.parseInt(machineJson.get("maxCoffeeCapacity").toString());
                    int maxWaterCapacity = Integer.parseInt(machineJson.get("maxWaterCapacity").toString());
                    String dateStr = (String) machineJson.get("created");
                    double price = Double.parseDouble(machineJson.get("price").toString());
                    Date manufactureDate = dateFormat.parse(dateStr);

                    CoffeeMachineNotAbstr machine = new CoffeeMachineNotAbstr(
                            id, type, model, power, maxCoffeeCapacity, maxWaterCapacity, manufactureDate, price);
                    machines.add(machine);
                    count++;
                } catch (Exception e) {
                    System.out.println("Error parsing machine from JSON: " + e.getMessage());
                }
            }
            System.out.println("Imported " + count + " machines from " + filename);
        } catch (Exception e) {
            System.out.println("Error importing from JSON: " + e.getMessage());
        }
        return machines;
    }

    private void createElement(Document doc, Element parent, String tag, String content)
    {
        Element element = doc.createElement(tag);
        element.appendChild(doc.createTextNode(content));
        parent.appendChild(element);
    }

    public void exportToXML(List<CoffeeMachineNotAbstr> machines, String filename) {
        try {
            DocumentBuilderFactory docFactory = DocumentBuilderFactory.newInstance();
            DocumentBuilder docBuilder = docFactory.newDocumentBuilder();
            Document doc = docBuilder.newDocument();

            Element rootElement = doc.createElement("coffeeMachines");
            doc.appendChild(rootElement);

            for (CoffeeMachineNotAbstr machine : machines)
            {
                Element machineElement = doc.createElement("machine");
                rootElement.appendChild(machineElement);

                machineElement.setAttribute("id", String.valueOf(machine.getId()));

                createElement(doc, machineElement, "type", machine.getType());
                createElement(doc, machineElement, "model", machine.getModel());
                createElement(doc, machineElement, "power", String.valueOf(machine.getPower()));
                createElement(doc, machineElement, "maxCoffeeCapacity", String.valueOf(machine.getMaxCoffeeCapacity()));
                createElement(doc, machineElement, "maxWaterCapacity", String.valueOf(machine.getMaxWaterCapacity()));
                createElement(doc, machineElement, "manufactureDate", dateFormat.format(machine.getManufactureDate()));
                createElement(doc, machineElement, "price", String.valueOf(machine.getPrice()));
            }

            TransformerFactory transformerFactory = TransformerFactory.newInstance();
            Transformer transformer = transformerFactory.newTransformer();
            DOMSource source = new DOMSource(doc);
            StreamResult result = new StreamResult(new File(filename));
            transformer.transform(source, result);

            System.out.println("Exported " + machines.size() + " machines to " + filename);
            System.out.println("File saved!");

        } catch (ParserConfigurationException | TransformerException pce) {
            System.out.println("Error exporting to XML: " + pce.getMessage());
            pce.printStackTrace();
        }
    }
    
}